#include <iostream>
#include <vector> 
#include <string>

//No pongo acentos en las gráficas ni en la terminal.

//Problema 1 de la tarea 6.


void Prob1(){
    TFile *file = TFile::Open("reco_run009776_00639.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");

    Double_t coreX; //Posición del núcleo en x
    Double_t coreY; //Posición del núcleo en y
    ULong64_t coreFitStatus; //Si esta variable vale cero, entonces se identificó correctamente el núcleo
    Int_t entradas = arbol->GetEntries();
    
    arbol->SetBranchAddress("rec.coreX", &coreX);
    arbol->SetBranchAddress("rec.coreY",&coreY);
    arbol->SetBranchAddress("rec.coreFitStatus",&coreFitStatus);

    char FileTit1[ ] = "Prob1.pdf";
    auto cvEv1 = new TCanvas("cb","Prob1",1500,750);
    TH2F *h1 = new TH2F("h1","Posici#acute{o}n de los n#acute{u}cleos de las cascadas atmosf#acute{e}ricas; Posici#acute{o}n en x; Posici#acute{o}n en y",1000,-500,500,1000,-400,800); 
    // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if (coreFitStatus == 0){
            h1->Fill(coreX,coreY);
        }
    } 
    h1->SetContour(50);
    //h1->SetMarkerColor(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(2);
    h1->Draw("colZ");
    //Esto es para mover la caja que tiene los datos estadísticos
    gPad->Update();
    TPaveStats *st = (TPaveStats*)h1->FindObject("stats");
    st->SetX1NDC(0.13); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st->SetX2NDC(0.27); //Posición final de la caja en x.



    cvEv1->cd(1);
    cvEv1->SaveAs(FileTit1);

}