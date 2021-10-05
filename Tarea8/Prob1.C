#include <iostream>



void Prob1(){
    TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    ULong64_t  nWHit; //Número de partículas que llegan al tanque.
    arbol->SetBranchAddress("HAWCSim.Evt.nWHit", &nWHit); 

    Long64_t WH_pType[1987];  
    arbol->SetBranchAddress("HAWCSim.WH.pType", WH_pType); 

    Long64_t Ev_pType; //Partícula primaria
    arbol->SetBranchAddress("HAWCSim.Evt.pType", &Ev_pType); 

    Double_t Evt_Energy; //Energía del rayo cósmico primario [GeV]. Con estas energías definiremos los rangos. 
    arbol->SetBranchAddress("HAWCSim.Evt.Energy", &Evt_Energy); 
    
    double NoParticulas[76]; //Hay a lo más 76 identificadores de partículas.
    ULong64_t NTot = 0; //Número total de partículas detectadas. 

    //Inicializamos a cero los arreglos.
    for(int i = 0; i<76; i++){
        NoParticulas[i] = 0;
    }

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        for(int j=0; j<nWHit; j++){
            int k = WH_pType[j];
            NoParticulas[k-1] += 1; //Los identificadores indexan desde uno, pero los arreglos indexan desde cero.
            NTot += 1;  
        }
    }

    //Al hacer el histograma nos damos cuenta de que no tiene sentido graficar más allá de 16.
    auto cvEv1 = new TCanvas("cb","hist1",600,550);
    TH1D *h1 = new TH1D("h1","Porcentaje de part#acute{i}culas que llegan a los detectores; Identificador de part#acute{i}cula; Porcentaje de detecci#acute{o}n",16,1,17); 
    for(int i=0; i<17; i++){
        NoParticulas[i] /= NTot; //Sacamos porcentajes.
        h1->SetBinContent(i+1,NoParticulas[i]);
    }

    h1->SetFillColor(2);
    h1->SetBarWidth(1);
    h1->GetXaxis()->SetNdivisions(16,0,0);
    h1->Draw();
    ////Para mover la caja de datos estadísticos////
    /*
    gPad->Update();
    TPaveStats *st = (TPaveStats*)h1->FindObject("stats");
    st->SetX1NDC(0.27); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st->SetX2NDC(0.40); //Posición final de la caja en x.
    st->SetY1NDC(0.8); 
    st->SetY2NDC(0.6);
    */
    /////////////////////////////////////////////////////
    cvEv1->cd(1);
    cvEv1->SaveAs("Prob1A.pdf");

    //El siguiente código es para definir los intervalos de energía que vamos a usar en la segunda parte de este problema.
    //Lo dejo comentado, pero se puede descomentar y funciona bien.
    
/*
    Int_t bins = 200; //Número de bins del histograma.
    Int_t mR = 1e5; //Rango maximo sobre el cual vamos a considerar valores de la energía.
    // Por encima de este valor ya no consideramos al resto de energías.

    auto cv2 = new TCanvas("cb2","hist2",600,550);
    TH1D *h2 = new TH1D("h2","Histograma de la energ#acute{i}a de rayos primarios; Energ#acute{i}a [GeV]; Cuentas",bins,0,mR); 
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        h2->Fill(Evt_Energy);
    }
    
    h2->SetFillColor(2);
    h2->SetBarWidth(1);
    h2->Draw();
    cv2->cd(1);
    cv2->SaveAs("Prob1B.pdf");

    //Para dividir nuestro conjunto de datos en tres rangos de energía, lo haremos tomando en cuenta
    //el área que barren por debajo del histograma.
    double A = h2->Integral(); //Obtenemos la integral del histograma.
    double A3=0;
    int b = 0;

    while (A3<=(A/3)){
        b += 1;
        A3 = h2->Integral(0,b); //Integral desde el bin 0 al bin b.
    }
    std::cout << "La primera tercera parte del area debajo del histograma se encuentra en el rango de energia 0-" << mR/bins * b << " GeV" <<std::endl;

    int c = b;
    A3 = 0;
    while (A3<=(A/3)){
        c +=1;
        A3 = h2->Integral(b,c);
    }
    std::cout << "El segundo rango de energia es " << mR/bins * b << "-" << mR/bins * c << "GeV" <<std::endl;
    std::cout << "El tercer rango de energia es " << mR/bins * c << "-" << mR << " GeV" << std::endl;
*/

//Los rangos de energía que resultan son: [0,2500GeV), [2500GeV,8500GeV) y [8500GeV, 1e5 GeV]
    double NoPartR1[76]; //Identificadores de partículas para el rango 1.
    double NoPartR2[76]; //Identificadores de partículas para el rango 2.
    double NoPartR3[76]; //Identificadores de partículas para el rango 3.
    ULong64_t NTotR1 = 0; //Número total de partículas detectadas. 
    ULong64_t NTotR2 = 0;
    ULong64_t NTotR3 = 0;

    //Inicializamos a cero los arreglos.
    for(int i = 0; i<76; i++){
        NoPartR1[i] = 0;
        NoPartR2[i] = 0;
        NoPartR3[i] = 0;
    }

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        for(int j=0; j<nWHit; j++){
            int k = WH_pType[j];
            if (Evt_Energy<2500){
                NoPartR1[k-1] += 1;
                NTotR1 += 1;
            }
            if (2500<=Evt_Energy && Evt_Energy<8500){
                NoPartR2[k-1] += 1;
                NTotR2 += 1;
            }
            if (8500<=Evt_Energy && Evt_Energy<=1e5){
                NoPartR3[k-1] += 1;
                NTotR3 += 1;
            }  
        }
    }

    auto cv3 = new TCanvas("cb3","hist3",600,550);
    TH1D *h3 = new TH1D("h3","Porcentaje de part#acute{i}culas que llegan a los detectores E#in[0, 2500 GeV); Identificador de part#acute{i}cula; Porcentaje de detecci#acute{o}n",16,1,17); 
    for(int i=0; i<17; i++){
        NoPartR1[i] /= NTotR1; //Sacamos porcentajes.
        h3->SetBinContent(i+1,NoPartR1[i]);
    }
    h3->SetFillColor(8);
    h3->SetBarWidth(1);
    h3->GetXaxis()->SetNdivisions(16,0,0);
    h3->Draw();
    cv3->cd(1);
    cv3->SaveAs("Prob1C1.pdf");

    auto cv4 = new TCanvas("cb4","hist4",600,550);
    TH1D *h4 = new TH1D("h4","Porcentaje de part#acute{i}culas que llegan a los detectores E#in[2500 GeV, 8500 GeV); Identificador de part#acute{i}cula; Porcentaje de detecci#acute{o}n",16,1,17); 
    for(int i=0; i<17; i++){
        NoPartR2[i] /= NTotR2; //Sacamos porcentajes.
        h4->SetBinContent(i+1,NoPartR2[i]);
    }
    h4->SetFillColor(6);
    h4->SetBarWidth(1);
    h4->GetXaxis()->SetNdivisions(16,0,0);
    h4->Draw();
    cv4->cd(1);
    cv4->SaveAs("Prob1C2.pdf");


    auto cv5 = new TCanvas("cb5","hist5",600,550);
    TH1D *h5 = new TH1D("h5","Porcentaje de part#acute{i}culas que llegan a los detectores E#in[8500 GeV, 1e5 GeV]; Identificador de part#acute{i}cula; Porcentaje de detecci#acute{o}n",16,1,17); 
    for(int i=0; i<17; i++){
        NoPartR3[i] /= NTotR3; //Sacamos porcentajes.
        h5->SetBinContent(i+1,NoPartR3[i]);
    }
    h5->SetFillColor(7);
    h5->SetBarWidth(1);
    h5->GetXaxis()->SetNdivisions(16,0,0);
    h5->Draw();
    cv5->cd(1);
    cv5->SaveAs("Prob1C3.pdf");

}
