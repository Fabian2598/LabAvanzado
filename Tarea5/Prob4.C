#include <iostream>


void Prob4(){
    TFile *file = TFile::Open("trig_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF"); 
    Int_t entradas = arbol->GetEntries();

    //Trabajamos nada más con pulsos de dos bordes.
    Int_t HitsMax = 2000; //Suponemos que a lo más tenemos 2,000 hits (Un PMT se puede disparar más de una vez)
    ULong64_t Hit2Edge;
    ULong64_t Hit4Edge;
    ULong64_t gpsNanosec;
    ULong64_t channelID_2Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 2 bordes
    Long64_t  hitTime_2Edge[HitsMax];
    ULong64_t channelID_4Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 4 bordes
    Long64_t  hitTime_4Edge[HitsMax];
    ULong64_t triggerFlags_2Edge[HitsMax];
    ULong64_t triggerFlags_4Edge[HitsMax];

    arbol->SetBranchAddress("trig.nHit4Edge", &Hit4Edge);
    arbol->SetBranchAddress("trig.nHit2Edge", &Hit2Edge); //No. de hits con 2 edges (pulso de baja amplitud)
    arbol->SetBranchAddress("trig.gpsNanosec",&gpsNanosec); //Este número nos dice a qué nanosegundo ocurrió el evento.

    arbol->SetBranchAddress("trig.channelID_2Edge",channelID_2Edge);
    arbol->SetBranchAddress("trig.hitTime_2Edge",hitTime_2Edge);
    arbol->SetBranchAddress("trig.triggerFlags_2Edge",triggerFlags_2Edge);

    arbol->SetBranchAddress("trig.channelID_4Edge",channelID_4Edge);
    arbol->SetBranchAddress("trig.hitTime_4Edge",hitTime_4Edge);
    arbol->SetBranchAddress("trig.triggerFlags_4Edge",triggerFlags_4Edge);

auto cvEv1 = new TCanvas("cb","hist1",1500,800);
TH2F *h1 = new TH2F("h1","Hits de 2 edges vs. trigger flag; Trigger flag; PMT ID;Cuentas",2,0,2,1200,1,1201);
h1->SetStats(0);
h1->SetContour(10);
for(int i=0; i<entradas;i++){
    arbol->GetEntry(i);
    for(int j=0; j<Hit2Edge; j++){
        h1->Fill(triggerFlags_2Edge[j],channelID_2Edge[j]);
    }
}
//h1->SetFillColor(2);
h1->GetXaxis()->SetNdivisions(2,0,0);
h1->GetXaxis()->SetLabelOffset(0.05);
h1->Draw("LEGO2");
cvEv1->cd(1);
cvEv1->SaveAs("Prob4Edge2.pdf");

auto cvEv2 = new TCanvas("cb2","hist2",1500,800);
TH2F *h2 = new TH2F("h2","Hits de 4 edges vs. trigger flag; Trigger flag; PMT ID; Cuentas",2,0,2,1200,1,1201);
h2->SetStats(0);
h2->SetContour(10);
for(int i=0; i<entradas;i++){
    arbol->GetEntry(i);
    for(int j=0; j<Hit4Edge; j++){
        h2->Fill(triggerFlags_4Edge[j],channelID_4Edge[j]);
    }
}
//h2->SetFillColor(2);
h2->GetZaxis()->SetMaxDigits(3); //Forzamos notación científica
h2->GetXaxis()->SetNdivisions(2,0,0);
h2->GetXaxis()->SetLabelOffset(0.05);
h2->Draw("LEGO2");
cvEv2->cd(1);
cvEv2->SaveAs("Prob4Edge4.pdf");

//Ahora para todos los hits
auto cvEv3 = new TCanvas("cb3","hist3",1500,800);
TH2F *h3 = new TH2F("h3","Hits de 4 y 2 edges vs. trigger flag; Trigger flag; PMT ID; Cuentas",2,0,2,1200,1,1201);
h3->SetStats(0);
h3->SetContour(10);
for(int i=0; i<entradas; i++){
    arbol->GetEntry(i);
    for(int j=0; j<Hit2Edge; j++){
        h3->Fill(triggerFlags_2Edge[j],channelID_2Edge[j]);
    }
    for(int j=0; j<Hit4Edge; j++){
        h3->Fill(triggerFlags_4Edge[j],channelID_4Edge[j]);
    }
}
//h3->SetFillColor(2);
h3->GetXaxis()->SetNdivisions(2,0,0);
h3->GetXaxis()->SetLabelOffset(0.05);
h3->Draw("LEGO2");
cvEv3->cd(1);
cvEv3->SaveAs("Prob4Edge2y4.pdf");
}