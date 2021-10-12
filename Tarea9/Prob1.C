#include <iostream>
#include <cmath>


void Prob1(){
    TFile *file = TFile::Open("gamma.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    Double_t  rec_coreX;
    Double_t  rec_coreY; //Coordenadas reconstruidas de los núcleos.
    Double_t  sim_coreX; 
    Double_t  sim_coreY; //Coordenadas simuladas de los núcleos
    ULong64_t cFs; //FiduScale

    arbol->SetBranchAddress("rec.coreX",&rec_coreX);
    arbol->SetBranchAddress("rec.coreY",&rec_coreY);
    arbol->SetBranchAddress("mc.coreX",&sim_coreX);
    arbol->SetBranchAddress("mc.coreY",&sim_coreY);
    arbol->SetBranchAddress("rec.coreFiduScale", &cFs);


//*************Eje X todos los eventos************//
    Int_t bins = 200; //Número de bins del histograma.
    Int_t mR = 200; //Rango máximo sobre el cual vamos a graficar.

    auto cv1 = new TCanvas("cb1","hist1",700,550);
    TH1D *h1 = new TH1D("Resoluci#acute{o}n en X","Histograma de la resoluci#acute{o}n en el eje X; |x_{rec}-x_{sim}| [m]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h1->Fill(abs(rec_coreX-sim_coreX));
    }
    h1->SetLineColor(9);
    h1->SetFillColor(9);
    h1->SetBarWidth(1);
    h1->Draw();

    TPaveText *tit = new TPaveText(0.25,0.95,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tit->AddText("Resoluci#acute{o}n en X");
    tit->SetBorderSize(0);
    tit->SetFillColor(gStyle->GetTitleFillColor());
    tit->Draw();
    cv1->SaveAs("Prob1A.pdf");

//***************Eje y todos los eventos*************//
    bins = 200;
    mR = 200;

    auto cv2 = new TCanvas("cb2","hist2",700,550);
    TH1D *h2 = new TH1D("Resoluci#acute{o}n en Y","Histograma de la resoluci#acute{o}n en el eje Y; |y_{rec}-y_{sim}| [m]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h2->Fill(abs(rec_coreY-sim_coreY));
    }
    h2->SetLineColor(kOrange+1);
    h2->SetFillColor(kOrange+1);
    h2->SetBarWidth(1);
    h2->Draw();

    TPaveText *tit2 = new TPaveText(0.25,0.95,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tit2->AddText("Resoluci#acute{o}n en Y");
    tit2->SetBorderSize(0);
    tit2->SetFillColor(gStyle->GetTitleFillColor());
    tit2->Draw();
    cv2->cd(1);
    cv2->SaveAs("Prob1B.pdf");

//Ahora apliquemos los filtros.

//*********Para el eje X FiduScale*********//
    bins = 200; //Número de bins del histograma.
    mR = 200; //Rango maximo sobre el cual vamos a graficar.

    auto cv3 = new TCanvas("cb3","hist3",700,550);
    TH1D *h3 = new TH1D("Resoluci#acute{o}n en X","Histograma de la resoluci#acute{o}n en el eje X, rec.coreFiduScale<50; |x_{rec}-x_{sim}| [m]; Cuentas",bins,0,mR); 
    TH1D *h4 = new TH1D("Resoluci#acute{o}n en X","Histograma de la resoluci#acute{o}n en el eje X, rec.coreFiduScale<100; |x_{rec}-x_{sim}| [m]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(cFs<100){ h3->Fill(abs(rec_coreX-sim_coreX)); }
        if(cFs<50){ h4->Fill(abs(rec_coreX-sim_coreX)); }
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

    auto legend = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("FiduScale","C");
    legend->AddEntry(h1,"FiduScale < 100");
    legend->AddEntry(h2,"FiduScale < 50");
    legend->Draw();

    //Para agregar el título del histograma.
    TPaveText *t = new TPaveText(0.25,0.95,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t->AddText("Resoluci#acute{o}n en X");
    t->SetBorderSize(0);
    t->SetFillColor(gStyle->GetTitleFillColor());
    t->Draw();
    cv3->cd(1);
    cv3->SaveAs("Prob1C.pdf");

//*********Para el eje Y FiduScale**********//
    bins = 200; //Número de bins del histograma.
    mR = 200; //Rango maximo sobre el cual vamos a graficar.

    auto cv4 = new TCanvas("cb4","hist4",700,550);
    TH1D *h5 = new TH1D("Resoluci#acute{o}n en Y","Histograma de la resoluci#acute{o}n en el eje Y, rec.coreFiduScale<50; |y_{rec}-y_{sim}| [m]; Cuentas",bins,0,mR); 
    TH1D *h6 = new TH1D("Resoluci#acute{o}n en Y","Histograma de la resoluci#acute{o}n en el eje Y, rec.coreFiduScale<100; |y_{rec}-y_{sim}| [m]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if(cFs<100){ h5->Fill(abs(rec_coreY-sim_coreY)); }
        if(cFs<50){ h6->Fill(abs(rec_coreY-sim_coreY)); }
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

    auto legend2 = new TLegend(0.7,0.7,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend2->SetHeader("FiduScale","C");
    legend2->AddEntry(h5,"FiduScale < 100");
    legend2->AddEntry(h6,"FiduScale < 50");
    legend2->Draw();

    //Para agregar el título del histograma.
    TPaveText *t2 = new TPaveText(0.25,0.95,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t2->AddText("Resoluci#acute{o}n en Y");
    t2->SetBorderSize(0);
    t2->SetFillColor(gStyle->GetTitleFillColor());
    t2->Draw();
    cv4->cd(1);
    cv4->SaveAs("Prob1D.pdf");

}
