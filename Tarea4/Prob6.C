#include <iostream>
#include <vector> 
#include <cmath>

//No pongo acentos

//Este código contiene el inciso 6) de la tarea.


void Prob6(){
    TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Int_t Canales = 1200; //A lo más se usan 1200 PMT
    ULong64_t nChannels; //Número de PMT usado en cada detector.
    ULong64_t channelIDInfo[Canales]; //Arreglo para extraer los ID de los PMT que se usaron en cada evento.
    ULong64_t channelCount[Canales]; //Número de veces que se activó cada PMT, cada elemento corresponde a un ID
    //de channelIDInfo.
    Double_t binWidth;

    arbol->SetBranchAddress("scaler.channelID", channelIDInfo);
    arbol->SetBranchAddress("scaler.nChannels", &nChannels);
    arbol->SetBranchAddress("scaler.channelCount", channelCount);
    arbol->SetBranchAddress("scaler.binWidth", &binWidth); //Está en milisegundos

    auto cb = new TCanvas("cb","cb",1200,550);
/////Primer evento
    arbol-> GetEntry(0); //Primer evento.
    Double_t TasaConteo[nChannels]; //Aquí guardaremos la tasa de conteo del primer evento.
      for(int i=0; i<nChannels; i++){
      TasaConteo[i] = channelCount[i]/(binWidth*1e-3); //En Hz
    }


    TH1F *h1 = new TH1F("TasaConteoPrimer","Tasa de conteo por PMT primer evento; PMT ID; Conteo [Khz]",Canales-1,1,Canales);
    for (int i=0; i<nChannels; i++){
      h1->SetBinContent(channelIDInfo[i],TasaConteo[i]*0.001);
    }


 //*****Último evento********//

    arbol-> GetEntry(999); //Último evento.
    std::cout << nChannels << std::endl;
    Double_t TasaConteo2[nChannels]; //Aquí guardaremos la tasa de conteo del primer evento.
      for(int i=0; i<nChannels; i++){
        TasaConteo2[i] = channelCount[i]/(binWidth*1e-3); //En Hz
    }

    
    TH1F *h2 = new TH1F("TasaConteoUltimo","Tasa de conteo por PMT ultimo evento; PMT ID; Conteo [Khz]",Canales-1,1,Canales);
    for (int i=0; i<nChannels; i++){
      h2->SetBinContent(channelIDInfo[i],TasaConteo2[i]*0.001);
    }
    TH1F *h3 = new TH1F("Fluctuacion","Fluctuacion en la tasa de conteo por PMT; PMT ID; Conteo [Khz]",Canales-1,1,Canales);
    for(int i=1; i<=Canales;i++){
        h3->SetBinContent(i,abs( h1->GetBinContent(i)-h2->GetBinContent(i)  ));
        std::cout << "Bin " << i << " Primer evento: " << h1->GetBinContent(i) << " ultimo evento " << h2->GetBinContent(i)  << std::endl;
        std::cout << "Canal " << channelIDInfo[i-1] << " Primer evento: " << TasaConteo[i-1]*0.001 <<" ultimo evento " << TasaConteo2[i-1]*0.001 << std::endl;
        std::cout << " " << std::endl; 
    }

    h3->SetFillColor(9);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    h3->Draw("BAR");
    cb->SaveAs("Fluctuaciones.pdf");



}