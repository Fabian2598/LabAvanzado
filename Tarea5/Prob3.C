#include <iostream>


void Prob3(){
    TFile *file = TFile::Open("trig_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    float TDCtoNS = 0.1; //1 canal de TDC es aproximadamente 1 ns.
    
    Int_t entradas = arbol->GetEntries();

    //Trabajamos nada más con pulsos de dos bordes.
    Int_t HitsMax = 2000; //Suponemos que a lo más tenemos 2,000 hits (Un PMT se puede disparar más de una vez)
    ULong64_t Hit2Edge;
    ULong64_t Hit4Edge;
    ULong64_t gpsNanosec;
    ULong64_t channelID_2Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 2 bordes
    ULong64_t flags_2Edge[HitsMax]; 
    Long64_t  hitTime_2Edge[HitsMax];
    ULong64_t channelID_4Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 4 bordes
    ULong64_t flags_4Edge[HitsMax]; 
    Long64_t  hitTime_4Edge[HitsMax];
    


    arbol->SetBranchAddress("trig.nHit4Edge", &Hit4Edge);
    arbol->SetBranchAddress("trig.nHit2Edge", &Hit2Edge); //No. de hits con 2 edges (pulso de baja amplitud)
    arbol->SetBranchAddress("trig.gpsNanosec",&gpsNanosec); //Este número nos dice a qué nanosegundo ocurrió el evento.
    arbol->SetBranchAddress("trig.channelID_2Edge",channelID_2Edge);
    arbol->SetBranchAddress("trig.hitTime_2Edge",hitTime_2Edge);
    arbol->SetBranchAddress("trig.flags_2Edge",flags_2Edge);
    arbol->SetBranchAddress("trig.channelID_4Edge",channelID_4Edge);
    arbol->SetBranchAddress("trig.hitTime_4Edge",hitTime_4Edge);
    arbol->SetBranchAddress("trig.flags_4Edge",flags_4Edge);

    float Freq2Edge[entradas];
    float Freq4Edge[entradas];
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        Freq2Edge[i] = Hit2Edge/(1.5); //Suponemos que cada evento dura 1.5 microsegundos. Ponemos los resultados en GhZ
        Freq4Edge[i] = Hit4Edge/(1.5);
    }

    

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv1 = new TCanvas("cb","hist1",1100,800);
    TH1F *h1 = new TH1F("h1","Numero de evento vs. frecuencia de hits de 2 edges; No. evento; Frecuencia [MHz]",entradas-1,1,entradas); 

    for(int i=0; i<entradas; i++){
        h1->SetBinContent(i+1,Freq2Edge[i]);
    } 

    //h1->SetLineColor(1);
    //h1->SetFillColor(7);
    h1->SetBarWidth(1);
    h1->SetStats(0);

    h1->Draw();
    cvEv1->cd(1);
    cvEv1->SaveAs("Prob32Edge.pdf");

    auto cvEv2 = new TCanvas("cb2","hist2",1100,800);
    TH1F *h2 = new TH1F("h2","Numero de evento vs. frecuencia de hits de 4 edges; No. evento; Frecuencia [MHz]",entradas-1,1,entradas); 
    h2->SetStats(0);

    for(int i=0; i<entradas; i++){
        h2->SetBinContent(i+1,Freq4Edge[i]);
    } 

    //h2->SetLineColor(1);
    //h2->SetFillColor(2);
    h2->SetBarWidth(1);
    h2->Draw();
    cvEv2->cd(1);
    cvEv2->SaveAs("Prob34Edge.pdf");
    
    auto cv = new TCanvas("cb3","hist3",1100,800);
    //gStyle->SetOptTitle(0);
    TH1F *h3 = new TH1F("h3","Numero de evento vs. frecuencia de hits de 2 y 4 edges; No. evento; Frecuencia [MHz]",entradas-1,1,entradas); 
   
    h3->SetStats(0);
    for(int i=0; i<entradas; i++){
        h3->SetBinContent(i+1,Freq2Edge[i]+Freq4Edge[i]);
    } 
    h3->SetBarWidth(1);
    h3->Draw();
    cv->cd(1);
    cv->SaveAs("Prob32y4Edge.pdf");


}