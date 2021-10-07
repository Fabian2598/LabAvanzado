#include <iostream>

void Prob4(){
    TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Double_t Evt_Energy; //Energía del rayo cósmico primario [GeV]. Con estas energías definiremos los rangos. 
    arbol->SetBranchAddress("HAWCSim.Evt.Energy", &Evt_Energy); 

    ULong64_t nPe; //Número de fotoelectrones detectados en el evento.
    arbol->SetBranchAddress("HAWCSim.Evt.nPE", &nPe);

    auto cv = new TCanvas("cb","hist",750,550);
    TH2D *h = new TH2D("h", "PEs detectados vs. energ#acute{i}a de rayos c#acute{o}smicos; PEs; E [GeV]",100,0,20000,100,0,1e5); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h->Fill(nPe,Evt_Energy);
    }
    h->SetContour(50);
    h->SetMarkerStyle(20);
    h->SetMarkerSize(4);
    h->Draw("colZ");
    gPad->Update();
    TPaveStats *st = (TPaveStats*) h->FindObject("stats");
    st->SetX1NDC(0.6);
    st->SetX2NDC(0.8);
    st->SetY1NDC(0.7);
    st->SetY2NDC(0.9);

    cv->cd(1);
    cv->SaveAs("Prob4A.pdf");

}
