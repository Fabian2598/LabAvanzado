#include <iostream>

//Problema 3 de la tarea 5.

void Prob3(){
    TFile *file = TFile::Open("trig_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    float TDCtoNS = 0.1; //1 canal de TDC es aproximadamente 1 ns.
    
    Int_t entradas = arbol->GetEntries();

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

    double Freq2Edge[1200]; 
    double Freq4Edge[1200];
    double Freq2y4Edge[1200];
    for(int i = 0; i<1200; i++){
        Freq2Edge[i] = 0;
        Freq4Edge[i] = 0;
        Freq2y4Edge[i] = 0;
    }

    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        int j = Hit2Edge;
        int k = Hit4Edge;
        
        Freq2Edge[j] += Hit2Edge; //Si se cuenta un número Hit2Edge en algún evento, entonces sumamos Hit2Edge a la entrada
        //enumerada por Hit2Edge a este arreglo. 
        Freq4Edge[k] += Hit4Edge;
        Freq2y4Edge[j+k] += j+k;

    }
for(int i = 0; i<1200; i++){
        Freq2Edge[i] /= 120; //El tiempo total del evento fueron dos minutos, por lo que dividimos entre 1200
        Freq4Edge[i] /= 120;
        Freq2y4Edge[i] /= 120;
    }
    

     auto cvEv1 = new TCanvas("cb","hist1",1100,800);
     TH1D *h1 = new TH1D("h1","Numero de hits de 2 edges vs. frecuencia; No. de Hits; Frecuencia [Hz]",400,1,401); 
     
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        //Graficamos hasta un rango máximo de 400 hits, ya que como se verá en la gráfica, la curva decae muy rápido.
        if (Hit2Edge<=400){
            int j = Hit2Edge;
            h1->SetBinContent(Hit2Edge,Freq2Edge[j]);
        }
    } 

    h1->SetFillColor(2);
    h1->SetBarWidth(1);
    h1->SetStats(0);

    h1->Draw();
    cvEv1->cd(1);
    cvEv1->SaveAs("Prob32Edge.pdf");



    auto cvEv2 = new TCanvas("cb2","hist2",1100,800);
    TH1F *h2 = new TH1F("h2","Numero de hits de 4 edges vs. frecuencia; No. de Hits; Frecuencia [Hz]",400-1,1,401); 
    h2->SetStats(0);

    for(int i=0; i<entradas; i++){
         arbol->GetEntry(i);
        if (Hit4Edge<=400){
            int j = Hit4Edge;
            h2->SetBinContent(Hit4Edge,Freq4Edge[j]);
        }
    } 

    h2->SetFillColor(2);
    h2->SetBarWidth(1);
    h2->Draw();
    cvEv2->cd(1);
    cvEv2->SaveAs("Prob34Edge.pdf");

    auto cvEv3 = new TCanvas("cb3","hist3",1100,800);
    TH1F *h3 = new TH1F("h3","Numero de hits de 2 y 4 edges vs. frecuencia; No. de Hits; Frecuencia [Hz]",400-1,1,401); 
    h3->SetStats(0);
    for(int i=0; i<entradas; i++){
         arbol->GetEntry(i);
        if ((Hit4Edge+Hit2Edge)<=400){
            int j = Hit4Edge + Hit2Edge;
            h3->SetBinContent(j,Freq2y4Edge[j]);
        }
    } 

    h3->SetFillColor(2);
    h3->SetBarWidth(1);
    h3->Draw();
    cvEv3->cd(1);
    cvEv3->SaveAs("Prob32y4Edge.pdf");
    
    //Ahora consideremos la combinación de ambos pulsos.


}