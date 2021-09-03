#include <iostream>
#include <vector> 

//No pongo acentos

//Este código contiene el inciso 7) de la tarea.


void Prob7(){
    TFile *file1 = TFile::Open("tdcscaler_run009776_00001.root");
    TFile *file2 = TFile::Open("tdcscaler_run009776_00173.root");
    TFile *file3 = TFile::Open("tdcscaler_run009776_00346.root");
    TFile *file4 = TFile::Open("tdcscaler_run009776_00519.root");
    TTree *arbol1 = (TTree*) file1 -> Get("XCDF");
    TTree *arbol2 = (TTree*) file2 -> Get("XCDF");
    TTree *arbol3 = (TTree*) file3 -> Get("XCDF");
    TTree *arbol4 = (TTree*) file4 -> Get("XCDF");
    
    ////********** Datos a extraer ********///
    ULong64_t m2CountSub1[300], m2CountSub2[300], m2CountSub3[300], m2CountSub4[300]; //Número de coincidencias dobles en cada tanque.
    ULong64_t m3CountSub1[300], m3CountSub2[300], m3CountSub3[300], m3CountSub4[300]; ; //Número de coincidencias triples en cada tanque.
    ULong64_t m4CountSub1[300], m4CountSub2[300], m4CountSub3[300], m4CountSub4[300]; ; //Coincidencias cuádruples
    ULong64_t nTanksSub1, nTanksSub2, nTanksSub3, nTanksSub4; //Número de taques 
    ULong64_t tankIDSub1[300], tankIDSub2[300], tankIDSub3[300], tankIDSub4[300];   //ID de los tanques. A lo más tenemos 300 tanques.
    Double_t binWidthSub1, binWidthSub2, binWidthSub3, binWidthSub4; //Ventana de tiempo del evento

    //***********Subrun 1**************//
    arbol1->SetBranchAddress("scaler.binWidth", &binWidthSub1); 
    arbol1->SetBranchAddress("scaler.nTanks", &nTanksSub1);
    arbol1->SetBranchAddress("scaler.tankID", tankIDSub1);
    arbol1->SetBranchAddress("scaler.multiplicity2Count", m2CountSub1);
    arbol1->SetBranchAddress("scaler.multiplicity3Count", m3CountSub1);
    arbol1->SetBranchAddress("scaler.multiplicity4Count", m4CountSub1);

    //***********Subrun 2**************//
    arbol2->SetBranchAddress("scaler.binWidth", &binWidthSub2); 
    arbol2->SetBranchAddress("scaler.nTanks", &nTanksSub2);
    arbol2->SetBranchAddress("scaler.tankID", tankIDSub2);
    arbol2->SetBranchAddress("scaler.multiplicity2Count", m2CountSub2);
    arbol2->SetBranchAddress("scaler.multiplicity3Count", m3CountSub2);
    arbol2->SetBranchAddress("scaler.multiplicity4Count", m4CountSub2);

    //***********Subrun 3**************//
    arbol3->SetBranchAddress("scaler.binWidth", &binWidthSub3); 
    arbol3->SetBranchAddress("scaler.nTanks", &nTanksSub3);
    arbol3->SetBranchAddress("scaler.tankID", tankIDSub3);
    arbol3->SetBranchAddress("scaler.multiplicity2Count", m2CountSub3);
    arbol3->SetBranchAddress("scaler.multiplicity3Count", m3CountSub3);
    arbol3->SetBranchAddress("scaler.multiplicity4Count", m4CountSub3);

    //***********Subrun 4**************//
    arbol4->SetBranchAddress("scaler.binWidth", &binWidthSub4); 
    arbol4->SetBranchAddress("scaler.nTanks", &nTanksSub4);
    arbol4->SetBranchAddress("scaler.tankID", tankIDSub4);
    arbol4->SetBranchAddress("scaler.multiplicity2Count", m2CountSub4);
    arbol4->SetBranchAddress("scaler.multiplicity3Count", m3CountSub4);
    arbol4->SetBranchAddress("scaler.multiplicity4Count", m4CountSub4);


   
//******************* Llenado de histogramas ********************//
    //Basta con cambiar el número de entrada y el nombre de los archivos en donde se van a guardas los histogramas.
    arbol1-> GetEntry(0); //Cada archivo tiene a lo más 5,000 entradas. 
    arbol2-> GetEntry(0); 
    arbol3-> GetEntry(0); 
    arbol4-> GetEntry(0); 
    //Nombre de los archivos que se van a guardar.
    const char NameFile1[ ] = "CoinDoblesSubruns.pdf";
    const char NameFile2[ ] = "CoinTriplesSubruns.pdf";
    const char NameFile3[ ] = "CoinCuadruplesSubruns.pdf";

    //Títulos de las gráficas
    const char Tit1[ ] = "Tasa de coincidencias multiples por detector. Primer evento.";
    const char Tit2[ ] = "Tasa de coincidencias triples por detector. Primer evento.";
    const char Tit3[ ] = "Tasa de coincidencias cuadruples por detector. Primer evento.";


    //Notación hmiSubj = histograma de coincidencias i subrun j

    //Tasas de conteo de las coincidencias.
    Double_t TC2Sub1[nTanksSub1], TC2Sub2[nTanksSub2], TC2Sub3[nTanksSub3], TC2Sub4[nTanksSub4];
    Double_t TC3Sub1[nTanksSub1], TC3Sub2[nTanksSub2], TC3Sub3[nTanksSub3], TC3Sub4[nTanksSub4];
    Double_t TC4Sub1[nTanksSub1], TC4Sub2[nTanksSub2], TC4Sub3[nTanksSub3], TC4Sub4[nTanksSub4];

    //*********SubRun1*********//
    for(int i =0; i<nTanksSub1; i++){
        TC2Sub1[i] = m2CountSub1[i]/(binWidthSub1*1e-3)*0.001; //Coincidencias múltiples KHz
        TC3Sub1[i] = m3CountSub1[i]/(binWidthSub1*1e-3)*0.001; //Coincidencias triples KHz
        TC4Sub1[i] = m4CountSub1[i]/(binWidthSub1*1e-3)*0.001; //Coincidencias dobles KHz
    } 
    //Declarando histogramas
    TH1F *hm2Sub1 = new TH1F("ConteoDobleSub1","Tasa de conteo de coincidencias dobles por tanque. Subrun1; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm3Sub1 = new TH1F("ConteoTripleSub1","Tasa de conteo de coincidencias triples por tanque. Subrun1; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm4Sub1 = new TH1F("ConteoCuadrupleSub1","Tasa de conteo de coincidencias cuadruples por tanque. Subrun1; Tank ID; Conteo [Khz]",300-1,1,300);

    //Llenando histogramas
    for (int i=0; i<nTanksSub1; i++){
      hm2Sub1->SetBinContent(tankIDSub1[i],m2CountSub1[i]);
      hm3Sub1->SetBinContent(tankIDSub1[i],m3CountSub1[i]);
      hm4Sub1->SetBinContent(tankIDSub1[i],m4CountSub1[i]);
    }

    //*********SubRun2*********//
    for(int i =0; i<nTanksSub2; i++){
        TC2Sub2[i] = m2CountSub2[i]/(binWidthSub2*1e-3)*0.001; //Coincidencias múltiples KHz
        TC3Sub2[i] = m3CountSub2[i]/(binWidthSub2*1e-3)*0.001; //Coincidencias triples KHz
        TC4Sub2[i] = m4CountSub2[i]/(binWidthSub2*1e-3)*0.001; //Coincidencias dobles KHz
    } 
    //Declarando histogramas
    TH1F *hm2Sub2 = new TH1F("ConteoDobleSub2","Tasa de conteo de coincidencias dobles por tanque. Subrun2; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm3Sub2 = new TH1F("ConteoTripleSub2","Tasa de conteo de coincidencias triples por tanque. Subrun2; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm4Sub2 = new TH1F("ConteoCuadrupleSub2","Tasa de conteo de coincidencias cuadruples por tanque. Subrun2; Tank ID; Conteo [Khz]",300-1,1,300);

    //Llenando histogramas
    for (int i=0; i<nTanksSub2; i++){
      hm2Sub2->SetBinContent(tankIDSub2[i],m2CountSub2[i]);
      hm3Sub2->SetBinContent(tankIDSub2[i],m3CountSub2[i]);
      hm4Sub2->SetBinContent(tankIDSub2[i],m4CountSub2[i]);
    }


    //*********SubRun3*********//
    for(int i =0; i<nTanksSub3; i++){
        TC2Sub3[i] = m2CountSub3[i]/(binWidthSub3*1e-3)*0.001; //Coincidencias múltiples KHz
        TC3Sub3[i] = m3CountSub3[i]/(binWidthSub3*1e-3)*0.001; //Coincidencias triples KHz
        TC4Sub3[i] = m4CountSub3[i]/(binWidthSub3*1e-3)*0.001; //Coincidencias dobles KHz
    } 
    //Declarando histogramas
    TH1F *hm2Sub3 = new TH1F("ConteoDobleSub3","Tasa de conteo de coincidencias dobles por tanque. Subrun3; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm3Sub3 = new TH1F("ConteoTripleSub3","Tasa de conteo de coincidencias triples por tanque. Subrun3; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm4Sub3 = new TH1F("ConteoCuadrupleSub3","Tasa de conteo de coincidencias cuadruples por tanque. Subrun3; Tank ID; Conteo [Khz]",300-1,1,300);

    //Llenando histogramas
    for (int i=0; i<nTanksSub3; i++){
      hm2Sub3->SetBinContent(tankIDSub3[i],m2CountSub3[i]);
      hm3Sub3->SetBinContent(tankIDSub3[i],m3CountSub3[i]);
      hm4Sub3->SetBinContent(tankIDSub3[i],m4CountSub3[i]);
    }


    //*********SubRun4*********//
    for(int i =0; i<nTanksSub4; i++){
        TC2Sub4[i] = m2CountSub4[i]/(binWidthSub4*1e-3)*0.001; //Coincidencias múltiples KHz
        TC3Sub4[i] = m3CountSub4[i]/(binWidthSub4*1e-3)*0.001; //Coincidencias triples KHz
        TC4Sub4[i] = m4CountSub4[i]/(binWidthSub4*1e-3)*0.001; //Coincidencias dobles KHz
    } 

    //Declarando histogramas
    TH1F *hm2Sub4 = new TH1F("ConteoDobleSub4","Tasa de conteo de coincidencias dobles por tanque. Subrun4; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm3Sub4 = new TH1F("ConteoTripleSub4","Tasa de conteo de coincidencias triples por tanque. Subrun4; Tank ID; Conteo [Khz]",300-1,1,300);
    TH1F *hm4Sub4 = new TH1F("ConteoCuadrupleSub4","Tasa de conteo de coincidencias cuadruples por tanque. Subrun4; Tank ID; Conteo [Khz]",300-1,1,300);

    //Llenando histogramas
    for (int i=0; i<nTanksSub4; i++){
      hm2Sub4->SetBinContent(tankIDSub4[i],m2CountSub4[i]);
      hm3Sub4->SetBinContent(tankIDSub4[i],m3CountSub4[i]);
      hm4Sub4->SetBinContent(tankIDSub4[i],m4CountSub4[i]);
    }

//****************** Gráficas ******************//

    //*********Coincidncias múltiples primer evento***********//
    auto cbMultEv1 = new TCanvas("cb","Coincidencias multiples",1200,600);

   

    gStyle->SetOptTitle(0); //Para quitar el título del histograma.
    
    
    //hm2Sub1->SetFillStyle(3305);
    hm2Sub1->SetLineColor(1);
    hm2Sub1->SetFillColorAlpha(4,0.80);
    hm2Sub1->SetBarWidth(1);
    hm2Sub1->SetStats(0);

    //hm2Sub2->SetFillStyle(3409);
    hm2Sub2->SetLineColor(1);
    hm2Sub2->SetFillColorAlpha(8,0.70);
    hm2Sub2->SetBarWidth(1);
    hm2Sub2->SetStats(0);


    //hm2Sub3->SetFillStyle(3005);
    hm2Sub3->SetLineColor(1);
    hm2Sub3->SetFillColorAlpha(6,0.60);
    hm2Sub3->SetBarWidth(1);
    hm2Sub3->SetStats(0);

    hm2Sub4->SetLineColor(1);
    hm2Sub4->SetFillColorAlpha(2,0.60);
    hm2Sub4->SetBarWidth(1);
    hm2Sub4->SetStats(0);

    hm2Sub1->Draw();
    hm2Sub2->Draw("same");
    hm2Sub3->Draw("same");
    hm2Sub4->Draw("same");

    auto legend = new TLegend(0.1,0.8,0.2,0.9); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("Subruns","C");
    legend->AddEntry(hm2Sub1,"Subrun1");
    legend->AddEntry(hm2Sub2,"Subrun2");
    legend->AddEntry(hm2Sub3,"Subrun3");
    legend->AddEntry(hm2Sub4,"Subrun4");
    legend->Draw();

    //Para agregar el título del histograma.
    TPaveText *t = new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    t->AddText(Tit1);
    t->SetBorderSize(0);
    t->SetFillColor(gStyle->GetTitleFillColor());
    t->Draw();
    cbMultEv1->cd(1);
    
    cbMultEv1->SaveAs(NameFile1);

//*********Coincidencias triples primer evento***********//
    auto cbTripEv1 = new TCanvas("cb","Coincidencias triples",1200,600);

    gStyle->SetOptTitle(0); //Para quitar el título del histograma.
        
    //hm2Sub1->SetFillStyle(3305);
    hm3Sub1->SetLineColor(1);
    hm3Sub1->SetFillColorAlpha(4,0.80);
    hm3Sub1->SetBarWidth(1);
    hm3Sub1->SetStats(0);

    //hm2Sub2->SetFillStyle(3409);
    hm3Sub2->SetLineColor(1);
    hm3Sub2->SetFillColorAlpha(8,0.70);
    hm3Sub2->SetBarWidth(1);
    hm3Sub2->SetStats(0);


    //hm2Sub3->SetFillStyle(3005);
    hm3Sub3->SetLineColor(1);
    hm3Sub3->SetFillColorAlpha(6,0.60);
    hm3Sub3->SetBarWidth(1);
    hm3Sub3->SetStats(0);

    hm3Sub4->SetLineColor(1);
    hm3Sub4->SetFillColorAlpha(2,0.60);
    hm3Sub4->SetBarWidth(1);
    hm3Sub4->SetStats(0);

    hm3Sub1->Draw();
    hm3Sub2->Draw("same");
    hm3Sub3->Draw("same");
    hm3Sub4->Draw("same");

    auto legendTripEv1 = new TLegend(0.1,0.8,0.2,0.9); //TLegend(x1,y1,x2,y2)
    legendTripEv1->SetHeader("Subruns","C");
    legendTripEv1->AddEntry(hm3Sub1,"Subrun1");
    legendTripEv1->AddEntry(hm3Sub2,"Subrun2");
    legendTripEv1->AddEntry(hm3Sub3,"Subrun3");
    legendTripEv1->AddEntry(hm3Sub4,"Subrun4");
    legendTripEv1->Draw();

    //Para agregar el título del histograma.
    TPaveText *tTripEv1= new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tTripEv1->AddText(Tit2);
    tTripEv1->SetBorderSize(0);
    tTripEv1->SetFillColor(gStyle->GetTitleFillColor());
    tTripEv1->Draw();

    cbTripEv1->cd(1);
    cbTripEv1->SaveAs(NameFile2);

//*********Coincidencias cúadruples primer evento*********//
auto cbCuadEv1 = new TCanvas("cb","Coincidencias cuadruples",1200,600);

    gStyle->SetOptTitle(0); //Para quitar el título del histograma.
        
    //hmIni2Sub1->SetFillStyle(3305);
    hm4Sub1->SetLineColor(1);
    hm4Sub1->SetFillColorAlpha(4,0.80);
    hm4Sub1->SetBarWidth(1);
    hm4Sub1->SetStats(0);

    //hm2Sub2->SetFillStyle(3409);
    hm4Sub2->SetLineColor(1);
    hm4Sub2->SetFillColorAlpha(8,0.70);
    hm4Sub2->SetBarWidth(1);
    hm4Sub2->SetStats(0);


    //hm2Sub3->SetFillStyle(3005);
    hm4Sub3->SetLineColor(1);
    hm4Sub3->SetFillColorAlpha(6,0.60);
    hm4Sub3->SetBarWidth(1);
    hm4Sub3->SetStats(0);

    hm4Sub4->SetLineColor(1);
    hm4Sub4->SetFillColorAlpha(2,0.60);
    hm4Sub4->SetBarWidth(1);
    hm4Sub4->SetStats(0);

    hm4Sub1->Draw();
    hm4Sub2->Draw("same");
    hm4Sub3->Draw("same");
    hm4Sub4->Draw("same");

    auto legendCuadEv1 = new TLegend(0.1,0.8,0.2,0.9); //TLegend(x1,y1,x2,y2)
    legendCuadEv1->SetHeader("Subruns","C");
    legendCuadEv1->AddEntry(hm4Sub1,"Subrun1");
    legendCuadEv1->AddEntry(hm4Sub2,"Subrun2");
    legendCuadEv1->AddEntry(hm4Sub3,"Subrun3");
    legendCuadEv1->AddEntry(hm4Sub4,"Subrun4");
    legendCuadEv1->Draw();

    //Para agregar el título del histograma.
    TPaveText *tCuadEv1= new TPaveText(0.25,0.9,0.8,1.0,"brNDC"); //TPaveText(x1,y1,x2,y2)
    tCuadEv1->AddText(Tit3);
    tCuadEv1->SetBorderSize(0);
    tCuadEv1->SetFillColor(gStyle->GetTitleFillColor());
    tCuadEv1->Draw();

    cbCuadEv1->cd(1);
    cbCuadEv1->SaveAs(NameFile3);


} 