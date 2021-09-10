#include <iostream>
#include <vector> 
#include <string>

//No pongo acentos en las gráficas o en la terminal.

//Inciso 1) de la tarea 5


void Prob1(){
    TFile *file = TFile::Open("trig_run009776_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    float TDCtoNS = 0.1; //1 canal de TDC es aproximadamente 1 ns.
    
    Int_t entradas = arbol->GetEntries();

    Int_t HitsMax = 2000; //Suponemos que a lo más tenemos 2,000 hits (Un PMT se puede disparar más de una vez)
    ULong64_t Hit2Edge;
    ULong64_t gpsNanosec;
    ULong64_t channelID_2Edge[HitsMax]; //ID con los canales de los PMT que detectaron pulsos con 2 bordes
    Long64_t  hitTime_2Edge[HitsMax];
   
    arbol->SetBranchAddress("trig.nHit2Edge", &Hit2Edge); //No. de hits con 2 edges (pulso de baja amplitud)
    arbol->SetBranchAddress("trig.channelID_2Edge",channelID_2Edge);
    arbol->SetBranchAddress("trig.hitTime_2Edge",hitTime_2Edge);
    arbol->SetBranchAddress("trig.gpsNanosec",&gpsNanosec); //Este número nos dice a qué nanosegundo ocurrió el evento.

    /**** Escaneando para encontrar eventos con muchos Hits***/ 
    /*
    for(int i = 0; i< entradas; i++){
        arbol->GetEntry(i);
        if (Hit4Edge>500 && Hit2Edge>500){
        std::cout << "Evento " << i << std::endl;
        std::cout << "nHit4 " << Hit4Edge << std::endl;
        std::cout << "nHit2 " << Hit2Edge << std::endl;
        std::cout << "" << std::endl;
        }

    }
    */

    //El inciso 1) lo haremos únicamente con pulsos 2Edge
    //Usaremos los eventos con etiquetados por: 6,944 - 17,310  - 13,773 - 30,719 - 24,809

    //********* Para el evento etiquetado por 6,944*********//
    int Ev = 6944;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec = to_string(gpsNanosec);
    char NSEV1[50];
    strcpy(NSEV1, NanSec.c_str());
    char Tit1[ ] = "Histograma de Tiempo vs. Canal. Evento 6,944. GPSNanoSec ";
    strcat(Tit1,NSEV1);
    strcat(Tit1,"; Tiempo [ns]; PMT ID");
    char FileTit1[ ] = "Prob1HistEv1.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv1 = new TCanvas("cb","Evento 1",1100,800);
    TH2F *h1 = new TH2F("h1",Tit1,1000,0,3000*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h1->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=3000){
            h1->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
        } 
    }
    h1->SetMarkerColor(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1);
    h1->Draw();
    cvEv1->cd(1);
    cvEv1->SaveAs(FileTit1);

    //********* Para el evento etiquetado por 17,310*********//

    Ev = 17310;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec2 = to_string(gpsNanosec);
    char NSEV2[50];
    strcpy(NSEV2, NanSec2.c_str());
    char Tit2[ ] = "Histograma de Tiempo vs. Canal. Evento 17,310. GPSNanoSec ";
    strcat(Tit2,NSEV2);
    strcat(Tit2,"; Tiempo [ns]; PMT ID");
    char FileTit2[ ] = "Prob1HistEv2.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 1500 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv2 = new TCanvas("cb2","Evento 2",1100,800);
    TH2F *h2 = new TH2F("h2",Tit2,1000,0,1500*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h2->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=1500){
            h2->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
        } 
    }
    h2->SetMarkerColor(2);
    h2->SetMarkerStyle(20);
    h2->SetMarkerSize(1);
    h2->Draw();
    cvEv2->cd(1);
    cvEv2->SaveAs(FileTit2);

    //********* Para el evento etiquetado por 13,773*********//

    Ev = 13773;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec3 = to_string(gpsNanosec);
    char NSEV3[50];
    strcpy(NSEV3, NanSec3.c_str());
    char Tit3[ ] = "Histograma de Tiempo vs. Canal. Evento 13,773. GPSNanoSec ";
    strcat(Tit3,NSEV3);
    strcat(Tit3,"; Tiempo [ns]; PMT ID");
    char FileTit3[ ] = "Prob1HistEv3.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000  TDC hay muchos hits que se ven correlacionados. 
    auto cvEv3 = new TCanvas("cb3","Evento 3",1100,800);
    TH2F *h3 = new TH2F("h3",Tit3,1000,0,3000*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h3->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=3000){
            h3->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
        } 
    }
    h3->SetMarkerColor(2);
    h3->SetMarkerStyle(20);
    h3->SetMarkerSize(1);
    h3->Draw();
    cvEv3->cd(1);
    cvEv3->SaveAs(FileTit3);

     //********* Para el evento etiquetado por 30,719*********//

    Ev = 30719;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec4 = to_string(gpsNanosec);
    char NSEV4[50];
    strcpy(NSEV4, NanSec4.c_str());
    char Tit4[ ] = "Histograma de Tiempo vs. Canal. Evento 30,719. GPSNanoSec ";
    strcat(Tit4,NSEV4);
    strcat(Tit4,"; Tiempo [ns]; PMT ID");
    char FileTit4[ ] = "Prob1HistEv4.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 2600 hay muchos hits que se ven correlacionados. 
    auto cvEv4 = new TCanvas("cb4","Evento 4",1100,800);
    TH2F *h4 = new TH2F("h4",Tit4,1000,0,2600*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h4->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=2600){
            h4->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
        } 
    }
    h4->SetMarkerColor(2);
    h4->SetMarkerStyle(20);
    h4->SetMarkerSize(1);
    h4->Draw();
    cvEv4->cd(1);
    cvEv4->SaveAs(FileTit4);

    //********* Para el evento etiquetado por 24,809*********//

    Ev=24809;
    arbol->GetEntry(Ev);
    //Título del histograma y del archivo PDF para guardarlo//
    std::string NanSec5 = to_string(gpsNanosec);
    char NSEV5[50];
    strcpy(NSEV5, NanSec5.c_str());
    char Tit5[ ] = "Histograma de Tiempo vs. Canal. Evento 24,809. GPSNanoSec ";
    strcat(Tit5,NSEV5);
    strcat(Tit5,"; Tiempo [ns]; PMT ID");
    char FileTit5[ ] = "Prob1HistEv5.pdf";
    /////////////////////////
    
    std::cout << "El evento numero " << Ev << " tiene " << Hit2Edge << " hits de 2Edge" << std::endl;

    //Podemos graficar primero en todo el rango de valores con este evento y nos daremos cuenta de que 
    //entre 0 y 3000 TDC hay muchos hits que se ven correlacionados. 
    auto cvEv5 = new TCanvas("cb5","Evento 5",1100,800);
    TH2F *h5 = new TH2F("h5",Tit5,1000,0,3000*TDCtoNS,1199,1,1200); // TH2F("h1","Título",xbinx,xmin,xmax,ybins,ymin,ymax)
    h5->SetStats(0);
    for(int i=0; i<Hit2Edge; i++){
        if (0<=hitTime_2Edge[i] && hitTime_2Edge[i]<=3000){
            h5->Fill(hitTime_2Edge[i]*TDCtoNS,channelID_2Edge[i]);
        } 
    }
    h5->SetMarkerColor(2);
    h5->SetMarkerStyle(20);
    h5->SetMarkerSize(1);
    h5->Draw();
    cvEv5->cd(1);
    cvEv5->SaveAs(FileTit5);



}