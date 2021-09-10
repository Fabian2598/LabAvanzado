#include <iostream>

/*Inciso 2) de la tarea 5.
De los eventos que usamos en el problema 1, trabajaremos con los que corresponden a las entradas 
13,773 y 24,809 del conjunto de datos.
*/
void Prob2(){
     TFile *file = TFile::Open("trig_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    float TDCtoNS = 0.1; //1 canal de TDC es aproximadamente 1 ns.
    
    Int_t entradas = arbol->GetEntries();

    //Trabajamos nada más con pulsos de dos bordes.
    Int_t HitsMax = 2000; //Suponemos que a lo más tenemos 2,000 hits (Un PMT se puede disparar más de una vez)
    ULong64_t Hit2Edge;
    ULong64_t gpsNanosec;
    ULong64_t channelID_2Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 2 bordes
    ULong64_t flags_2Edge[HitsMax]; 
    Long64_t  hitTime_2Edge[HitsMax];
   
    arbol->SetBranchAddress("trig.nHit2Edge", &Hit2Edge); //No. de hits con 2 edges (pulso de baja amplitud)
    arbol->SetBranchAddress("trig.channelID_2Edge",channelID_2Edge);
    arbol->SetBranchAddress("trig.hitTime_2Edge",hitTime_2Edge);
    arbol->SetBranchAddress("trig.gpsNanosec",&gpsNanosec); //Este número nos dice a qué nanosegundo ocurrió el evento.
    arbol->SetBranchAddress("trig.flags_2Edge",flags_2Edge);
    
    //********* Para el evento etiquetado por 13,773*********//
    int Ev = 13773;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec = to_string(gpsNanosec);
    char NSEV[50];
    strcpy(NSEV, NanSec.c_str());
    char Tit[ ] = "Histograma de Tiempo vs. Canal con corte de calidad. Evento 13,773. GPSNanoSec ";
    strcat(Tit,NSEV);
    strcat(Tit,"; Tiempo [ns]; PMT ID");
    char FileTit[ ] = "Prob2HistEv1.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv1 = new TCanvas("cb","Evento 1",1100,800);
    TH2F *h1 = new TH2F("h1",Tit,1000,0,3000*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h1->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=3000){
            //Agregamos este if para el filtro de calidad. FLAG = 0 implica que la medición es buena.
            if(flags_2Edge[i] == 0){
                 h1->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
            }
           
        } 
    }
    h1->SetMarkerColor(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1);
    h1->Draw();
    cvEv1->cd(1);
    cvEv1->SaveAs(FileTit);

     //********* Para el evento etiquetado por 24,809 *********//
    Ev = 24809 ;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec2 = to_string(gpsNanosec);
    char NSEV2[50];
    strcpy(NSEV2, NanSec2.c_str());
    char Tit2[ ] = "Histograma de Tiempo vs. Canal con corte de calidad. Evento 24,809. GPSNanoSec ";
    strcat(Tit2,NSEV2);
    strcat(Tit2,"; Tiempo [ns]; PMT ID");
    char FileTit2[ ] = "Prob2HistEv2.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv2 = new TCanvas("c2","Evento 2",1100,800);
    TH2F *h2 = new TH2F("h2",Tit2,1000,0,3000*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h2->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=3000){
            //Agregamos este if para el filtro de calidad. FLAG = 0 implica que la medición es buena.
            if(flags_2Edge[i] == 0){
                 h2->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
            }
           
        } 
    }
    h2->SetMarkerColor(2);
    h2->SetMarkerStyle(20);
    h2->SetMarkerSize(1);
    h2->Draw();
    cvEv2->cd(1);
    cvEv2->SaveAs(FileTit2);
}