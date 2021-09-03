#include <iostream>
#include <vector> 

//No pongo acentos

//Este código contiene el inciso 5) de la tarea.


void Prob5(){
    TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

   
    ULong64_t multiplicity2Count[300]; //Número de coincidencias dobles en cada tanque.
    ULong64_t multiplicity3Count[300]; //Número de coincidencias triples en cada tanque.
    ULong64_t multiplicity4Count[300]; //Coincidencias cuádruples
    ULong64_t nTanks; //Número de taques 
    ULong64_t tankID[300];   //ID de los tanques. A lo más tenemos 300 tanques.
    Double_t binWidth; //Ventana de tiempo del evento

    arbol->GetEntry(0); // Primer evento.

    //Guardamos todos los datos. 

    arbol->SetBranchAddress("scaler.binWidth", &binWidth); //Está en milisegundos
    arbol->SetBranchAddress("scaler.nTanks", &nTanks);
    arbol->SetBranchAddress("scaler.tankID", tankID);
    arbol->SetBranchAddress("scaler.multiplicity2Count", multiplicity2Count);
    arbol->SetBranchAddress("scaler.multiplicity3Count", multiplicity3Count);
    arbol->SetBranchAddress("scaler.multiplicity4Count", multiplicity4Count);

   
//******************* PRIMER EVENTO ********************//
    arbol-> GetEntry(0); 

    //Tasas de conteo de las coincidencias.
    Double_t TasaConteo2[nTanks];
    Double_t TasaConteo3[nTanks];
    Double_t TasaConteo4[nTanks];
    for(int i =0; i<nTanks; i++){
        TasaConteo2[i] = multiplicity2Count[i]/(binWidth*1e-3); //Coincidencias múltiples
        TasaConteo3[i] = multiplicity3Count[i]/(binWidth*1e-3); //Coincidencias triples
        TasaConteo4[i] = multiplicity4Count[i]/(binWidth*1e-3); //Coincidencias dobles

    } 
    
    auto cb = new TCanvas("cb","cb",700,1200);
    cb->Divide(1,3);
    TH1F *h1 = new TH1F("TasaConteoDoble","Tasa de conteo de coincidencias dobles por tanque, primer evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h1->SetBinContent(tankID[i],TasaConteo2[i]*0.001);
    }
 
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.05);
    h1->GetXaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->SetFillColor(9);
    h1->SetBarWidth(1);
    h1->SetStats(0);
    cb->cd(1);
    h1->Draw("BAR");

    TH1F *h2 = new TH1F("TasaConteoTriple","Tasa de conteo de coincidencias triples por tanque, primer evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h2->SetBinContent(tankID[i],TasaConteo3[i]*0.001);
    }
    h2->GetXaxis()->SetLabelSize(0.05);
    h2->GetYaxis()->SetLabelSize(0.05);
    h2->GetXaxis()->SetTitleSize(0.05);
    h2->GetYaxis()->SetTitleSize(0.05);
    h2->SetFillColor(9);
    h2->SetBarWidth(1);
    h2->SetStats(0);
    cb->cd(2);
    h2->Draw("BAR");

    TH1F *h3 = new TH1F("TasaConteoCuadruple","Tasa de conteo de coincidencias cuadruples por tanque, primer evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h3->SetBinContent(tankID[i],TasaConteo4[i]*0.001);
    }
    h3->GetXaxis()->SetLabelSize(0.05);
    h3->GetYaxis()->SetLabelSize(0.05);
    h3->GetXaxis()->SetTitleSize(0.05);
    h3->GetYaxis()->SetTitleSize(0.05);
    h3->SetFillColor(9);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    cb->cd(3);
    h3->Draw("BAR");
    cb->SaveAs("Prob5PrimerEvento.pdf");

   //******************ÚLTIMO EVENTO********************//

    arbol-> GetEntry(999); 

    //Tasas de conteo de las coincidencias.
    Double_t TasaConteo22[nTanks];
    Double_t TasaConteo32[nTanks];
    Double_t TasaConteo42[nTanks];
    for(int i =0; i<nTanks; i++){
        TasaConteo22[i] = multiplicity2Count[i]/(binWidth*1e-3); //Coincidencias múltiples
        TasaConteo32[i] = multiplicity3Count[i]/(binWidth*1e-3); //Coincidencias triples
        TasaConteo42[i] = multiplicity4Count[i]/(binWidth*1e-3); //Coincidencias dobles

    } 
    
    auto cb2 = new TCanvas("cb2","cb2",700,1200);
    cb2->Divide(1,3);
    TH1F *h12 = new TH1F("TasaConteoDoble","Tasa de conteo de coincidencias dobles por tanque, ultimo evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h12->SetBinContent(tankID[i],TasaConteo22[i]*0.001);
    }
 
    h12->GetXaxis()->SetLabelSize(0.05);
    h12->GetYaxis()->SetLabelSize(0.05);
    h12->GetXaxis()->SetTitleSize(0.05);
    h12->GetYaxis()->SetTitleSize(0.05);
    h12->SetFillColor(9);
    h12->SetBarWidth(1);
    h12->SetStats(0);
    cb2->cd(1);
    h12->Draw("BAR");

    TH1F *h22 = new TH1F("TasaConteoTriple","Tasa de conteo de coincidencias triples por tanque, ultimo evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h22->SetBinContent(tankID[i],TasaConteo32[i]*0.001);
    }
    h22->GetXaxis()->SetLabelSize(0.05);
    h22->GetYaxis()->SetLabelSize(0.05);
    h22->GetXaxis()->SetTitleSize(0.05);
    h22->GetYaxis()->SetTitleSize(0.05);
    h22->SetFillColor(9);
    h22->SetBarWidth(1);
    h22->SetStats(0);
    cb2->cd(2);
    h22->Draw("BAR");

    TH1F *h32 = new TH1F("TasaConteoCuadruple","Tasa de conteo de coincidencias cuadruples por tanque, ulrimo evento; Tank ID; Conteo [Khz]",300-1,1,300);
    for (int i=0; i<nTanks; i++){
      h32->SetBinContent(tankID[i],TasaConteo42[i]*0.001);
    }
    h32->GetXaxis()->SetLabelSize(0.05);
    h32->GetYaxis()->SetLabelSize(0.05);
    h32->GetXaxis()->SetTitleSize(0.05);
    h32->GetYaxis()->SetTitleSize(0.05);
    h32->SetFillColor(9);
    h32->SetBarWidth(1);
    h32->SetStats(0);
    cb2->cd(3);
    h32->Draw("BAR");
    cb2->SaveAs("Prob5UltimoEvento.pdf");

}