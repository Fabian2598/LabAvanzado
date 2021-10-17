#include <iostream>
#include <cmath>

//Revisar si la correlación es lineal. Los ejes deberían decir 10^1, 10^2, 10^3, etc...
void Prob4(){
    TFile *fileg = TFile::Open("gamma.root"); //Fotones
    TFile *filep = TFile::Open("protons.root"); //Protones
    TTree *arbolg = (TTree*) fileg -> Get("XCDF");
    TTree *arbolp =  (TTree*) filep -> Get("XCDF");
    Int_t entradas_g = arbolg->GetEntries();
    Int_t entradas_p = arbolg->GetEntries();

    //*******Fotones*******//
    Double_t  Esim_G; arbolg->SetBranchAddress("SimEvent.energyTrue",&Esim_G); //Energía simulada GeV
    Double_t  theta_G; arbolg->SetBranchAddress("SimEvent.thetaTrue",&theta_G); //Distibución angular theta
    Double_t  phi_G; arbolg->SetBranchAddress("SimEvent.phiTrue",&phi_G); // Distribución angular phi
    //*******Protones*******//
    Double_t  Esim_P; arbolp->SetBranchAddress("SimEvent.energyTrue",&Esim_P); //Energía simulada GeV
    Double_t  theta_P; arbolp->SetBranchAddress("SimEvent.thetaTrue",&theta_P); //Distibución angular theta
    Double_t  phi_P; arbolp->SetBranchAddress("SimEvent.phiTrue",&phi_P); // Distribución angular phi

    auto cv = new TCanvas("cb","hist",750,550);
    TH1D *h1 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primari E#in [1 TeV,50 TeV], #theta<20#circ; E_{sim} [GeV]; Cuentas",100,1e4,50e4); 
    TH1D *h2 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primario; E_{sim} [GeV]; Cuentas",100,1e4,50e4); 
    for(int i=0; i<entradas_g; i++){
        arbolg->GetEntry(i);
        if (Esim_G>1e4 && Esim_G<50e4){
            if(theta_G<20){
                h1->Fill(Esim_G); //Energía del rayo primario.
            }
        }

    }
    h1->SetLineColor(9);
    h1->SetFillColorAlpha(9,0.6);
    h1->SetBarWidth(1);
    h1->SetStats(0);
    h1->GetYaxis()->SetRangeUser(0,30);
    h1->Draw();

    for(int i=0; i<entradas_p; i++){
        arbolp->GetEntry(i);
        if (Esim_P>1e4 && Esim_P<50e4){
            if(theta_P<20){
                h1->Fill(Esim_P); //Energía del rayo primario.
            }
        }
    }
    h2->SetLineColor(kOrange+1);
    h2->SetFillColorAlpha(kOrange+1,0.6);
    h2->SetBarWidth(1);
    h2->SetStats(0);
    h2->Draw("Same");
    
    auto legend = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("Part#acute{i}cula","C");
    legend->AddEntry(h1,"E #gamma");
    legend->AddEntry(h2,"E p");
    legend->Draw();

    TPaveText *tit = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tit->AddText("Distribuci#acute{o}n de energ#acute{i}a del rayo primario E#in [1 TeV,50 TeV], #theta<20#circ");
    tit->SetBorderSize(0);
    tit->SetFillColor(gStyle->GetTitleFillColor());
    tit->Draw();

    cv->cd(1);
    cv->SaveAs("Prob4A.pdf");

//***********Distribución angular***************//


    auto cv2 = new TCanvas("cb2","hist",750,550);
    TH1D *h3 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primario; #theta [#circ]; Cuentas",100,0,90); 
    TH1D *h4 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primario; #theta [#circ]; Cuentas",100,0,90); 
    for(int i=0; i<entradas_g; i++){
        arbolg->GetEntry(i);
        h3->Fill(theta_G); //Energía del rayo primario.
    }
    h3->SetLineColor(9);
    h3->SetFillColorAlpha(9,0.6);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    h3->GetYaxis()->SetRangeUser(0,1200);
    h3->Draw();

    for(int i=0; i<entradas_p; i++){
        arbolp->GetEntry(i);
        h4->Fill(theta_P); //Energía del rayo primario.
    }
    h4->SetLineColor(kOrange+1);
    h4->SetFillColorAlpha(kOrange+1,0.6);
    h4->SetBarWidth(1);
    h4->SetStats(0);
    h4->Draw("Same");
    
    auto legend2 = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend2->SetHeader("Part#acute{i}cula","C");
    legend2->AddEntry(h3,"E #gamma");
    legend2->AddEntry(h4,"E p");
    legend2->Draw();


    TPaveText *tit2 = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tit2->AddText("Distribuci#acute{o}n angular #theta");
    tit2->SetBorderSize(0);
    tit2->SetFillColor(gStyle->GetTitleFillColor());
    tit2->Draw();


    cv2->cd(1);
    cv2->SaveAs("Prob4B.pdf");


    auto cv3 = new TCanvas("cb3","hist",750,550);
    TH1D *h5 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primario; #phi [#circ]; Cuentas",360,0,360); 
    TH1D *h6 = new TH1D("Energ#acute{i}a #gamma", "Distribuci#acute{o}n de energ#acute{i}a del rayo primario; #phi [#circ]; Cuentas",360,0,360); 
    for(int i=0; i<entradas_g; i++){
        arbolg->GetEntry(i);
        h5->Fill(phi_G); //Energía del rayo primario.
    }
    h5->SetLineColor(9);
    h5->SetFillColorAlpha(9,0.6);
    h5->SetBarWidth(1);
    h5->SetStats(0);
    h5->GetYaxis()->SetRangeUser(0,200);
    h5->Draw();

    for(int i=0; i<entradas_p; i++){
        arbolp->GetEntry(i);
        h6->Fill(phi_P); //Energía del rayo primario.
    }
    h6->SetLineColor(kOrange+1);
    h6->SetFillColorAlpha(kOrange+1,0.6);
    h6->SetBarWidth(1);
    h6->SetStats(0);
    h6->Draw("Same");
    
    auto legend3 = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend3->SetHeader("Part#acute{i}cula","C");
    legend3->AddEntry(h3,"E #gamma");
    legend3->AddEntry(h4,"E p");
    legend3->Draw();

    TPaveText *tit3 = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tit3->AddText("Distribuci#acute{o}n angular #phi");
    tit3->SetBorderSize(0);
    tit3->SetFillColor(gStyle->GetTitleFillColor());
    tit3->Draw();

    cv3->cd(1);
    cv3->SaveAs("Prob4C.pdf");
}