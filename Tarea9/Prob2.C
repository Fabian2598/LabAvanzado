#include <iostream>
#include <cmath>


void Prob2(){
    TFile *file = TFile::Open("gamma.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Double_t  pi = 3.14159265359;
    Double_t  rec_zenith;
    Double_t  rec_azimuth; //Ángulos reconstruidos
    Double_t  sim_zenith; 
    Double_t  sim_azimuth; //Ángulos simulados.
    ULong64_t cFs; //coreFiduScale.
    ULong64_t nHit;

    arbol->SetBranchAddress("rec.zenithAngle",&rec_zenith);
    arbol->SetBranchAddress("rec.azimuthAngle",&rec_azimuth);
    arbol->SetBranchAddress("mc.zenithAngle",&sim_zenith);
    arbol->SetBranchAddress("mc.azimuthAngle",&sim_azimuth);
    arbol->SetBranchAddress("rec.coreFiduScale", &cFs);
    arbol->SetBranchAddress("event.nHit", &nHit);

//*************Zenith, dividiendo por número de eventos************//
    Int_t bins = 50; //Número de bins del histograma.
    Int_t mR = 10; //Rango máximo sobre el cual vamos a graficar.

    auto cv1 = new TCanvas("cb1","hist1",700,550);
    TH1D *h1 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo cenital","Histograma de la resoluci#acute{o}n del #acute{a}ngulo cenital, nHit<100; |#theta_{rec}-#theta_{sim}| [#circ]; Cuentas",bins,0,mR); 
    TH1D *h2 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo cenital","Histograma de la resoluci#acute{o}n del #acute{a}ngulo cenital, nHit>100; |#theta_{rec}-#theta_{sim}| [#circ]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(nHit<100){h1->Fill(abs(rec_zenith-sim_zenith)*180/pi);}
        if(nHit>100){h2->Fill(abs(rec_zenith-sim_zenith)*180/pi);}
    }
    h1->SetLineColor(9);
    h1->SetFillColorAlpha(9,0.6);
    h1->SetBarWidth(1);
    h1->SetStats(0);
    h1->Draw();

    h2->SetLineColor(kOrange+1);
    h2->SetFillColorAlpha(kOrange+1,0.6);
    h2->SetBarWidth(1);
    h2->SetStats(0);
    h2->Draw("Same");
    

    gStyle->SetOptTitle(0); //Para quitar el título del histograma.

    auto legend = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("nHits","C");
    legend->AddEntry(h1,"nHits < 100");
    legend->AddEntry(h2,"nHits > 100");
    legend->Draw();

    //Para agregar el título del histograma.
    TPaveText *t = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t->AddText("Resoluci#acute{o}n del #acute{a}ngulo cenital");
    t->SetBorderSize(0);
    t->SetFillColor(gStyle->GetTitleFillColor());
    t->Draw();
    cv1->cd(1);
    cv1->SaveAs("Prob2A.pdf");


    //********Zenith, FiduScale*********//

    auto cv2 = new TCanvas("cb2","hist2",700,550);
    TH1D *h3 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo cenital","Histograma de la resoluci#acute{o}n del #acute{a}ngulo cenital, nHit<100; |#theta_{rec}-#theta_{sim}| [#circ]; Cuentas",bins,0,mR); 
    TH1D *h4 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo cenital","Histograma de la resoluci#acute{o}n del #acute{a}ngulo cenital, nHit>100; |#theta_{rec}-#theta_{sim}| [#circ]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(cFs<100){h3->Fill(abs(rec_zenith-sim_zenith)*180/pi);}
        if(cFs<50){h4->Fill(abs(rec_zenith-sim_zenith)*180/pi);}
    }
    h3->SetLineColor(9);
    h3->SetFillColorAlpha(9,0.6);
    h3->SetBarWidth(1);
    h3->SetStats(0);
    h3->Draw();

    h4->SetLineColor(kOrange+1);
    h4->SetFillColorAlpha(kOrange+1,0.6);
    h4->SetBarWidth(1);
    h4->SetStats(0);
    h4->Draw("Same");
    
    gStyle->SetOptTitle(0); //Para quitar el título del histograma.

    auto legend2 = new TLegend(0.6,0.6,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend2->SetHeader("coreFiduScale","C");
    legend2->AddEntry(h3,"coreFiduScale < 100");
    legend2->AddEntry(h4,"coreFiduScale < 50");
    legend2->Draw();

    //Para agregar el título del histograma.
    TPaveText *t2 = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t2->AddText("Resoluci#acute{o}n del #acute{a}ngulo cenital");
    t2->SetBorderSize(0);
    t2->SetFillColor(gStyle->GetTitleFillColor());
    t2->Draw();
    cv2->cd(1);
    cv2->SaveAs("Prob2B.pdf");


//*************Azimuth, dividiendo por número de eventos************//
    auto cv3 = new TCanvas("cb3","hist3",700,550);
    TH1D *h5 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo acimutal","Histograma de la resoluci#acute{o}n del #acute{a}ngulo acimutal, nHit<100; |#phi_{rec}-#phi_{sim}| [#circ]; Cuentas",bins,0,mR); 
    TH1D *h6 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo acimutal","Histograma de la resoluci#acute{o}n del #acute{a}ngulo acimutal, nHit>100; |#phi_{rec}-#phi_{sim}| [#circ]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(nHit<100){h5->Fill(abs(rec_azimuth-sim_azimuth)*180/pi);}
        if(nHit>100){h6->Fill(abs(rec_azimuth-sim_azimuth)*180/pi);}
    }
    h5->SetLineColor(kViolet+1);
    h5->SetFillColorAlpha(kViolet+1,0.6);
    h5->SetBarWidth(1);
    h5->SetStats(0);
    h5->Draw();

    h6->SetLineColor(kTeal-9);
    h6->SetFillColorAlpha(kTeal-9,0.6);
    h6->SetBarWidth(1);
    h6->SetStats(0);
    h6->Draw("Same");
    
    gStyle->SetOptTitle(0); //Para quitar el título del histograma.

    auto legend3 = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend3->SetHeader("nHits","C");
    legend3->AddEntry(h5,"nHits < 100");
    legend3->AddEntry(h6,"nHits > 100");
    legend3->Draw();

    //Para agregar el título del histograma.
    TPaveText *t3 = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t3->AddText("Resoluci#acute{o}n del #acute{a}ngulo acimutal");
    t3->SetBorderSize(0);
    t3->SetFillColor(gStyle->GetTitleFillColor());
    t3->Draw();
    cv3->cd(1);
    cv3->SaveAs("Prob2C.pdf");


//********Azimuth FiduScale***********//
    auto cv4 = new TCanvas("cb4","hist4",700,550);
    TH1D *h7 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo acimutal","Histograma de la resoluci#acute{o}n del #acute{a}ngulo acimutal, nHit<100; |#phi_{rec}-#phi_{sim}| [#circ]; Cuentas",bins,0,mR); 
    TH1D *h8 = new TH1D("Resoluci#acute{o}n del #acute{a}ngulo acimutal","Histograma de la resoluci#acute{o}n del #acute{a}ngulo acimutal, nHit>100; |#phi_{rec}-#phi_{sim}| [#circ]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(cFs<100){h7->Fill(abs(rec_azimuth-sim_azimuth)*180/pi);}
        if(cFs<50){h8->Fill(abs(rec_azimuth-sim_azimuth)*180/pi);}
    }
    h7->SetLineColor(kViolet+1);
    h7->SetFillColorAlpha(kViolet+1,0.6);
    h7->SetBarWidth(1);
    h7->SetStats(0);
    h7->Draw();

    h8->SetLineColor(kTeal-9);
    h8->SetFillColorAlpha(kTeal-9,0.6);
    h8->SetBarWidth(1);
    h8->SetStats(0);
    h8->Draw("Same");
    
    gStyle->SetOptTitle(0); //Para quitar el título del histograma.

    auto legend4 = new TLegend(0.6,0.6,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend4->SetHeader("coreFiduScale","C");
    legend4->AddEntry(h7,"coreFiduScale < 100");
    legend4->AddEntry(h8,"coreFiduScale < 50");
    legend4->Draw();

    //Para agregar el título del histograma.
    TPaveText *t4 = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t4->AddText("Resoluci#acute{o}n del #acute{a}ngulo acimutal");
    t4->SetBorderSize(0);
    t4->SetFillColor(gStyle->GetTitleFillColor());
    t4->Draw();
    cv4->cd(1);
    cv4->SaveAs("Prob2D.pdf");
}

