#include <iostream>

//Problema 3 de la tarea 6.
//Para responder la pregunta A(B), se revisa el número de entradas en el histograma, que correspondan a nhits > 100 (500)
//en una ventana de 10 ns (20 ns) y se divide entre el tiempo total del evento, que son como 125 segundos.

void Prob3(){
    TFile *file = TFile::Open("reco_run009776_00639.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    ULong64_t  nHitSP10;
    ULong64_t  nHitSP20;
    arbol->SetBranchAddress("rec.nHitSP10", &nHitSP10); //No. de hits en una ventana de 10 ns
    arbol->SetBranchAddress("rec.nHitSP20", &nHitSP20); //No. de hits en una venta de 20 ns
    

    double Freq10Ns[1200]; //Suponemos que a lo más puede a ver 1200 Hits en una ventana de 10 ns
    double Freq20Ns[1200];
    double Freq100Hits = 0; //Frecuencia de eventos con más de 100 hits para ventana de 10ns
    double Freq500Hits = 0; //Frecuencia de eventos con más de 500 hits para ventana de 20ns

    //Inicializamos a cero los arreglos.
    for(int i = 0; i<1200; i++){
        Freq10Ns[i] = 0;
        Freq20Ns[i] = 0;
    }

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        int j = nHitSP10;
        int k = nHitSP20;
        
        Freq10Ns[j] += 1; //Si se cuenta un número nHitSP10 en algún evento, entonces sumamos 1 a la entrada
        //enumerada por nHitSP10 a este arreglo. 
        Freq20Ns[k] += 1;

        if (j>100){Freq100Hits+=1;}
        if (k>500){Freq500Hits+=1;}
    }

    std::cout << "Para una ventana de 10 ns, la frecuencia de eventos con mas de 100 hits es " << Freq100Hits/125 << " Hz" << std::endl;
    std::cout << "Para una ventana de 20 ns, la frecuencia de eventos con mas de 500 hits es " << Freq500Hits/125 << " Hz" << std::endl;

    auto cvEv1 = new TCanvas("cb","hist1",1500,750);
    TH1D *h1 = new TH1D("h1","N#acute{u}mero de hits en ventana de 10 ns vs. frecuencia; No. de Hits; Frecuencia [Hz]",400,1,401); 
     
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        //Graficamos hasta un rango máximo de 400 hits, ya que como se verá en la gráfica, la curva decae muy rápido.
        if (nHitSP10<=400){
            int j = nHitSP10;
            h1->SetBinContent(j,Freq10Ns[j]/125); //El archivo dura aproximadamente 125 segundos
        }
    } 

    h1->SetFillColor(2);
    h1->SetBarWidth(1);
        //Esto es para mover la caja que tiene los datos estadísticos
    h1->Draw();
    gPad->Update();
    TPaveStats *st = (TPaveStats*)h1->FindObject("stats");
    st->SetX1NDC(0.27); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st->SetX2NDC(0.40); //Posición final de la caja en x.


    cvEv1->cd(1);
    cvEv1->SaveAs("Prob310Ns.pdf");

    auto cvEv2 = new TCanvas("cb2","hist2",1500,750);
    TH1F *h2 = new TH1F("h2","N#acute{u}mero de hits en ventana de  20 ns vs. frecuencia; No. de Hits; Frecuencia [Hz]",400,1,401); 
   

    for(int i=0; i<entradas; i++){
         arbol->GetEntry(i);
        if (nHitSP20<=400){
            int j = nHitSP20;
            h2->SetBinContent(j,Freq20Ns[j]/125);
        }
    } 
    h2->Draw();
    gPad->Update();
    TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");
    st2->SetX1NDC(0.27); //Posición inicial de la caja en X. Está en coordenadas normalizadas de 0 a 1.
    st2->SetX2NDC(0.40); //Posición final de la caja en x.
    h2->SetFillColor(2);
    h2->SetBarWidth(1);

    cvEv2->cd(1);
    cvEv2->SaveAs("Prob320Ns.pdf");

}