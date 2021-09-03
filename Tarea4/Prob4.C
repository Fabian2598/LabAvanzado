#include <iostream>
#include <vector> 

//No pongo acentos

//Este código contiene el inciso 4) de la tarea.


void Prob4(){
    TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Int_t Canales = 1200; //A lo más se usan 1200 PMT
    ULong64_t nChannels; //Número de PMT usado en cada detector.
    ULong64_t channelIDInfo[Canales]; //Arreglo para extraer los ID de los PMT que se usaron en cada evento.
    ULong64_t GPSSecond; //Tiempo al que ocurrió el evento.
    ULong64_t channelCount[Canales]; //Número de veces que se activó cada PMT, cada elemento corresponde a un ID
    //de channelIDInfo.
    ULong64_t nTanks; //Número de detectores 
    ULong64_t tankID[300];   //ID de los tanques. A lo más tenemos 300 tanques.
    ULong64_t channelTankID[Canales]; //Id del tanque al que pertenecen los PMT 
    Double_t binWidth; //Ventana de tiempo del evento

    arbol->GetEntry(0); // Primer evento.

    //Guardamos todos los datos. 
    arbol->SetBranchAddress("scaler.channelID", channelIDInfo);
    arbol->SetBranchAddress("scaler.GPSSecond", &GPSSecond);
    arbol->SetBranchAddress("scaler.nChannels", &nChannels);
    arbol->SetBranchAddress("scaler.channelCount", channelCount);
    arbol->SetBranchAddress("scaler.binWidth", &binWidth); //Está en milisegundos
    arbol->SetBranchAddress("scaler.nTanks", &nTanks);
    arbol->SetBranchAddress("scaler.tankID", tankID);
    arbol->SetBranchAddress("scaler.channelTankID",channelTankID);

    arbol-> GetEntry(0); //Primer evento.
    Double_t TasaConteo[nTanks]; //Aquí guardaremos la tasa de conteo del primer evento para cada tanque usado.
    int i = 0, j=0;
    while(i<nChannels){
        TasaConteo[j] = channelCount[i];
        while(channelTankID[i]==channelTankID[i+1]){
            TasaConteo[j] += channelCount[i+1]/(binWidth*1e-3); //En Hz
            i+=1;
            }    
        j+=1;
        i+=1;
    }
    //std::cout << TasaConteo[0] << std::endl;

    auto cb = new TCanvas("cb","cb",1200,550);
    cb->Divide(2,1);
    TH1F *h1 = new TH1F("TasaConteo","Tasa de conteo por tanque primer evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h1->SetBinContent(tankID[i],TasaConteo[i]*0.001);
    }
    h1->SetFillColor(9);
    h1->SetBarWidth(1);
    h1->SetStats(0);
    //h1->SetBarOffset(-0.25); Para mover las barras de los histogramas
    cb->cd(1);
    h1->Draw("BAR");

    //Hacemos una gráfica similar pero sólamente para los primeros 40 tanques para ver un poco mejor al inicio.
   int NoTanque=40;
   auto *h2 = new TH1F("TasaConteo2","Tasa de conteo por tanque primer evento; Tank ID; Conteo [Khz]",tankID[NoTanque]-1,1,tankID[NoTanque]);
   h2->SetFillColor(9);
   h2->SetBarWidth(1);
   h2->SetStats(0);
   for (int i=0;i<NoTanque;i++){
      h2->SetBinContent(tankID[i],TasaConteo[i]*0.001);
   }
   cb->cd(2);
   h2->Draw("BAR same");
   cb->SaveAs("Prob4PrimerEvento.pdf");

   //***********************Último evento**********************//

    arbol-> GetEntry(999); //Último evento.
    Double_t TasaConteo2[nTanks]; //Aquí guardaremos la tasa de conteo del primer evento para cada tanque.
    i = 0, j=0;
    while(i<nChannels){
        TasaConteo2[j] = channelCount[i];
        while(channelTankID[i]==channelTankID[i+1]){
            TasaConteo2[j] += channelCount[i+1]/(binWidth*1e-3); //En Hz
            i+=1;
            }    
        j+=1;
        i+=1;
    }
    auto cb2 = new TCanvas("cb2","cb2",1200,550);
    cb2->Divide(2,1);
    TH1F *h3 = new TH1F("TasaConteo3","Tasa de conteo por tanque ultimo evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h3->SetBinContent(tankID[i],TasaConteo2[i]*0.001);
    }
 
    h3->SetFillColor(9);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    cb2->cd(1);
    h3->Draw("BAR");

    //Hacemos una gráfica similar pero sólamente para los primeros 40 tanques para ver un poco mejor al inicio.
   auto *h4 = new TH1F("TasaConteo4","Tasa de conteo por tanque ultimo evento; Tank ID; Conteo [Khz]",tankID[NoTanque]-1,1,tankID[NoTanque]);
   h4->SetFillColor(9);
   h4->SetBarWidth(1);
   h4->SetStats(0);
   for (int i=0;i<NoTanque;i++){
      h4->SetBinContent(tankID[i],TasaConteo2[i]*0.001);
   }
   cb2->cd(2);
   h4->Draw("BAR same");
   cb2->SaveAs("Prob4UltimoEvento.pdf");


}
