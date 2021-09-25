#include <iostream>
#include <vector> 

//No pongo acentos en las gráficas ni en la terminal.


void Prob5(){
    TFile *file = TFile::Open("reco_run009776_00639.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    
    Int_t entradas = arbol->GetEntries();
    Double_t pi = 3.14159265359;
    Double_t  azimuthAngle;
    ULong64_t  angleFitStatus;
    arbol->SetBranchAddress("rec.azimuthAngle", &azimuthAngle); 
    arbol->SetBranchAddress("rec.angleFitStatus", &angleFitStatus); 
    
     auto cvEv1 = new TCanvas("cb","hist1",1500,750);
     TH1D *h1 = new TH1D("h1","Distribuci#acute{o}n del #acute{a}ngulo azimutal para todas las cascadas atmosf#acute{e}ricas, sin corte de selecci#acute{o}n.; #acute{A}ngulo azimutal [grados]; Cuentas",360,-180,180); 
     
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h1->Fill(azimuthAngle*180/pi); 
    } 
    h1->SetMaximum(10000);
    h1->SetFillColor(2);
    h1->SetBarWidth(1);
    h1->Draw();
    gPad->Update();
    TPaveStats *st = (TPaveStats*)h1->FindObject("stats");
    st->SetX1NDC(0.13); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st->SetX2NDC(0.27); //Posición final de la caja en x.

    
    cvEv1->cd(1);
    cvEv1->SaveAs("Prob5A.pdf");

    //Ahora con corte de calidad.


    auto cvEv2 = new TCanvas("cb2","hist2",1500,750);
    TH1D *h2 = new TH1D("h2","Distribuci#acute{o}n del #acute{a}ngulo azimutal para todas las cascadas atmosf#acute{e}ricas, con corte de selecci#acute{o}n.; #acute{A}ngulo azimutal [grados]; Cuentas; Cuentas",360,-180,180); 
    float FdE = 0;
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        if (angleFitStatus == 0){
            FdE += 1;
            h2->Fill(azimuthAngle*180/pi);
        }
    } 
    std::cout << "La fraccion total de eventos que pasan por el filtro de seleccion es " << FdE/entradas << std::endl;
    h2->SetFillColor(2);
    h2->SetBarWidth(1);
    h2->Draw();

    gPad->Update();
    TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    st2->SetX1NDC(0.45); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st2->SetX2NDC(0.57); //Posición final de la caja en x.

    cvEv2->cd(1);
    cvEv2->SaveAs("Prob5B.pdf");

    //Ahora con corte de calidad.










}
