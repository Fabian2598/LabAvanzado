#include <iostream>
#include <vector> 

//No pongo acentos

//Este código contiene el inciso 1), 2) y 3) de la tarea.


void Prob3(){
    TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Int_t Canales = 1200; //A lo más se usan 1200 PMT
    ULong64_t nChannels; //Número de PMT usado en cada detector.
    ULong64_t channelIDInfo[Canales]; //Arreglo para extraer los ID de los PMT que se usaron en cada evento.
    ULong64_t GPSSecond; //Tiempo al que ocurrió el evento.
    ULong64_t channelCount[Canales]; //Número de veces que se activó cada PMT, cada elemento corresponde a un ID
    //de channelIDInfo.
    Double_t binWidth;

    arbol->SetBranchAddress("scaler.channelID", channelIDInfo);
    arbol->SetBranchAddress("scaler.GPSSecond", &GPSSecond);
    arbol->SetBranchAddress("scaler.nChannels", &nChannels);
    arbol->SetBranchAddress("scaler.channelCount", channelCount);
    arbol->SetBranchAddress("scaler.binWidth", &binWidth); //Está en milisegundos

    //*********************Pregunta 1) y 2) de la parte A de la tarea*****************************//
    arbol->GetEntry(0); //Los primeros eventos fueron registrados al mismo GPSSecond=1293625808.
    // De acuerdo con https://www.andrews.edu/~tzs/timeconv/timedisplay.php, este número corresponde 
    //al día 2 de enero de 2021 a las  02, 2021	12:29:50
    ULong64_t ini=GPSSecond, fin;
    std::cout<< "Primeros eventos registrados al GPS time " << ini << std::endl; 
    std::cout<<  "2 de enero de 2021 a las 7:29:50 \n" << std::endl;
    arbol->GetEntry(entradas-1); //Los últimos eventos fueron registrados al mismo GPSSecond=1293625808.
    // De acuerdo con https://www.andrews.edu/~tzs/timeconv/timedisplay.php, este número corresponde 
    //Enero 02, 2021	12:30:14
    fin = GPSSecond;
    std::cout<< "Ultimos eventos registrados al GPS time " << fin << std::endl; 
    std::cout<< "2 de enero de 2021 a las 7:30:14 \n" << std::endl;

  //Podemos saber la ventana de tiempo que abarca el archivo de datos simplemente restando los GPS time
    std::cout << "Segundos GPS entre el primer y el ultimo evento: " << fin-ini << std::endl;
    std::cout << "Es decir, la ventana de tiempo de todas las mediciones fue de 24 segundos. \n" << std::endl;
    //***************************************************************************************************//

    //******************************Histogramas*************************************//

    /////Primer evento
    arbol-> GetEntry(0); //Primer evento.
    Double_t TasaConteo[nChannels]; //Aquí guardaremos la tasa de conteo del primer evento.
      for(int i=0; i<nChannels; i++){
      TasaConteo[i] = channelCount[i]/(binWidth*1e-3); //En Hz
    }

    auto cb = new TCanvas("cb","cb",1200,550);
    cb->Divide(2,1);
    TH1F *h1 = new TH1F("TasaConteo","Tasa de conteo por PMT primer evento; PMT ID; Conteo [Khz]",nChannels-1,1,nChannels);
    for (int i=0; i<nChannels; i++){
      h1->SetBinContent(channelIDInfo[i],TasaConteo[i]*0.001);
    }
    h1->SetFillColor(9);
    h1->SetBarWidth(1);
    h1->SetStats(0);
    //h1->SetBarOffset(-0.25); Para mover las barras de los histogramas
    cb->cd(1);
    h1->Draw("BAR");
  //Hacemos una gráfica similar pero sólamente para los primeros 40 PMT para ver un poco mejor al inicio.
   auto *h2 = new TH1F("TasaConteo2","Tasa de conteo por PMT primer evento; PMT ID; Conteo [Khz]",channelIDInfo[40]-1,1,channelIDInfo[40]);
   h2->SetFillColor(9);
   h2->SetBarWidth(1);
   h2->SetStats(0);
   for (int i=0;i<40;i++){
      h2->SetBinContent(channelIDInfo[i],TasaConteo[i]*0.001);
   }
   cb->cd(2);
   h2->Draw("BAR same");
   cb->SaveAs("Prob3PrimerEvento.pdf");
///////////////////////////////////////
   arbol-> GetEntry(999); //Último evento.
    Double_t TasaConteo2[nChannels]; //Aquí guardaremos la tasa de conteo del primer evento.
      for(int i=0; i<nChannels; i++){
      TasaConteo2[i] = channelCount[i]/(binWidth*1e-3); //En Hz
    }

    auto cb2 = new TCanvas("cb2","cb2",1200,550);
    cb2->Divide(2,1);
    TH1F *h3 = new TH1F("TasaConteo3","Tasa de conteo por PMT ultimo evento; PMT ID; Conteo [Khz]",Canales-1,1,Canales);
    for (int i=0; i<nChannels; i++){
      h3->SetBinContent(channelIDInfo[i],TasaConteo2[i]*0.001);
    }
    h3->SetFillColor(9);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    cb2->cd(1);
    h3->Draw("BAR");
  //Hacemos una gráfica similar pero sólamente para los primeros 40 PMT para ver un poco mejor al inicio.
   auto *h4 = new TH1F("TasaConteo4","Tasa de conteo por PMT ultimo evento; PMT ID; Conteo [Khz]",channelIDInfo[40]-1,1,channelIDInfo[40]);
   h4->SetFillColor(9);
   h4->SetBarWidth(1);
   h4->SetStats(0);
   for (int i=0;i<40;i++){
      h4->SetBinContent(channelIDInfo[i],TasaConteo2[i]*0.001);
   }
   cb2->cd(2);
   h4->Draw("BAR same");
   cb2->SaveAs("Prob3UltimoEvento.pdf");

 

    
}