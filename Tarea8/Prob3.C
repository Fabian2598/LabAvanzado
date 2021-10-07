#include <iostream>

void Prob3(){
    TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    ULong64_t  nWHit; //Número de partículas que llegan al tanque.
    arbol->SetBranchAddress("HAWCSim.Evt.nWHit", &nWHit); 
    
    Double_t Theta; arbol->SetBranchAddress("HAWCSim.Evt.Theta", &Theta); 
    Double_t Phi; arbol->SetBranchAddress("HAWCSim.Evt.Phi", &Phi); 

    auto cvT = new TCanvas("cb","#theta",600,550);
    TH1D *h1 = new TH1D("#theta","Distribuci#acute{o}n angular #theta; #theta [#circ]; Cuentas",90,0,90); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h1->Fill(Theta);
    }
    h1->SetLineColor(9);
    h1->SetFillColor(9);
    h1->SetBarWidth(1);
    h1->Draw();
    cvT->cd(1);
    cvT->SaveAs("Prob3A.pdf");

    auto cvP = new TCanvas("cb2","#phi",600,550);
    TH1D *h2 = new TH1D("#phi","Distribuci#acute{o}n angular #phi; #phi [#circ]; Cuentas",360,0,360); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h2->Fill(Phi);
    }
    h2->SetLineColor(kOrange+1);
    h2->SetFillColor(kOrange+1);
    h2->SetBarWidth(1);
    h2->Draw();
    cvP->cd(1);
    cvP->SaveAs("Prob3B.pdf");
}