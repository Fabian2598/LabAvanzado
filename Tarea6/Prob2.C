#include <iostream>
#include <vector> 
#include <string>


//Problema 2 de la tarea 6.



void Prob2(){
    TFile *file = TFile::Open("reco_run009776_00639.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");

    Double_t pi = 3.14159265359;
    Double_t dec;
    Double_t ra;
    ULong64_t angleFitStatus;; //Si esta variable vale cero, entonces se tiene buena calidad de la reconstrucción angular
    Int_t entradas = arbol->GetEntries();
    
    arbol->SetBranchAddress("rec.dec", &dec); //Declinación
    arbol->SetBranchAddress("rec.ra",&ra); //Ascensión recta
    arbol->SetBranchAddress("rec.angleFitStatus",&angleFitStatus);


    char FileTit1[ ] = "Prob2.pdf";
    auto cvEv1 = new TCanvas("cb","Prob2",1500,750);
    TH2F *h1 = new TH2F("h1","Direcciones reconstruidas de las cascadas atmosf#acute{e}ricas; Declinaci#acute{o}n en grados; Ascensi#acute{o}n recta en grados",179,-90,90,359,0,360); 
    // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if (angleFitStatus == 0){
            h1->Fill(dec * 180/pi,ra * 180/pi); //Guardamos todo en grados
        }
    } 
    //Usamos 100 bins
    h1->SetContour(500);
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