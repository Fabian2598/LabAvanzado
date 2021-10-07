#include <iostream>
#include <TMath.h>


void Prob2(){
    TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");
    Int_t entradas = arbol->GetEntries();

    ULong64_t  nWHit; //Número de partículas que llegan al tanque.
    arbol->SetBranchAddress("HAWCSim.Evt.nWHit", &nWHit); 

    Long64_t WH_pType[1987];  //Identificadores de las partículas secundarias.
    arbol->SetBranchAddress("HAWCSim.WH.pType", WH_pType); 

    Long64_t Ev_pType; //Partícula primaria
    arbol->SetBranchAddress("HAWCSim.Evt.pType", &Ev_pType); 

    Double_t Evt_Energy; //Energía del rayo cósmico primario [GeV]. 
    arbol->SetBranchAddress("HAWCSim.Evt.Energy", &Evt_Energy); 

    Double_t  WH_Energy[1987];  //Energía de las partículas secundarias [GeV].
    arbol->SetBranchAddress("HAWCSim.WH.Energy", WH_Energy);

    Double_t CoreX; arbol->SetBranchAddress("HAWCSim.Evt.X", &CoreX); //Posición x del núcleo de la cascada (cm)
    Double_t CoreY; arbol->SetBranchAddress("HAWCSim.Evt.Y", &CoreY);  //Posición y del núcleo de la cascada (cm)

    Double_t XNE[1987];  arbol->SetBranchAddress("HAWCSim.WH.XNE", XNE); 
     //Posición en Y de la interacción (dónde golpea la partícula secundaria en el tanque) [cm]
    Double_t YNE[1987]; arbol->SetBranchAddress("HAWCSim.WH.YNE", YNE); 
      //Posición en Y de la interacción (dónde golpea la partícula secundaria en el tanque) [cm]

//Para encontrar eventos con por lo menos 70 hits por encima de 1 GeV se puede usar el siguiente código.
/*
for(int i=0; i<entradas; i++){
    int NHitsUmbral = 0;
    arbol->GetEntry(i);
    for(int j=0; j<nWHit; j++){
        if (WH_Energy[j]>=1){NHitsUmbral+=1;}
    }
    if(NHitsUmbral>=70){std::cout<<"El evento " << i << " supera el umbral minimo de hits, pues tiene " << NHitsUmbral << " hits con mas de 1 gev"  <<  std::endl;}
}
*/

//**********************Distribución lateral evento 1**********************//
    int N = 1; //El evento 1 tiene más de 70 hits con energía superior a 1 GeV.
    arbol->GetEntry(N);

    std::cout << "El evento " << N << " tiene " << nWHit << " hits" << std::endl;
    std::cout << "" << std::endl;

    std::string NoEntrada = to_string(N);
    char NoEntradaChar[50];
    strcpy(NoEntradaChar, NoEntrada.c_str());
    char Tit1[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit1,NoEntradaChar);

    auto cvEv1 = new TCanvas("cb","Prob2",700,500);
    auto gr = new TGraphErrors();  gr->SetMarkerColor(8); gr->SetMarkerSize(0.6); gr->SetMarkerStyle(8);
    for(int i=0; i<nWHit; i++){
        gr->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
   }
   gr->SetTitle(Tit1);
   gr->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   gr->GetXaxis()->SetLimits(0,120);
   gr->GetYaxis()->SetTitle("E [GeV]");
   gr->SetMinimum(0);
   gr->SetMaximum(5);
   gr->Draw("AP");

   TLine *l = new TLine(0,1,120,1);
   l->Draw();
   cvEv1->cd(1);
   cvEv1->SaveAs("Prob2A.pdf");


//**********************Distribución lateral evento 25**********************//
    N = 25; //El evento 25 tiene más de 70 hit cpn energía superior a 1 GeV.
    arbol->GetEntry(N);

    std::cout << "El evento " << N << " tiene " << nWHit << " hits" << std::endl;
    std::cout << "" << std::endl;
   
    std::string NoEntrada2 = to_string(N);
    char NoEntradaChar2[50];
    strcpy(NoEntradaChar2, NoEntrada2.c_str());
    char Tit2[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit2,NoEntradaChar2);

    auto cvEv2 = new TCanvas("cb2","Prob2",700,500);
    auto g2 = new TGraphErrors();  g2->SetMarkerColor(8); g2->SetMarkerSize(0.6); g2->SetMarkerStyle(8);
    for(int i=0; i<nWHit; i++){
        g2->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
   }
   g2->SetTitle(Tit2);
   g2->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   g2->GetXaxis()->SetLimits(0,120);
   g2->GetYaxis()->SetTitle("E [GeV]");
   g2->SetMinimum(0);
   g2->SetMaximum(5);
   g2->Draw("AP");

   TLine *l2 = new TLine(0,1,120,1);
   l2->Draw();
   cvEv2->cd(1);
   cvEv2->SaveAs("Prob2B.pdf");


//**********************Distribución lateral evento 198**********************//
    N = 198; //El evento 198 tiene más de 70 hits con una energía superior a 1 GeV.
    arbol->GetEntry(N);

    std::cout << "El evento " << N << " tiene " << nWHit << " hits" << std::endl;
    std::cout << "" << std::endl;
   
    std::string NoEntrada3 = to_string(N);
    char NoEntradaChar3[50];
    strcpy(NoEntradaChar3, NoEntrada3.c_str());
    char Tit3[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit3,NoEntradaChar3);

    auto cvEv3 = new TCanvas("cb3","Prob2",700,500);
    auto g3 = new TGraphErrors();  g3->SetMarkerColor(8); g3->SetMarkerSize(0.6); g3->SetMarkerStyle(8);
    for(int i=0; i<nWHit; i++){
        g3->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
   }
   g3->SetTitle(Tit3);
   g3->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   g3->GetXaxis()->SetLimits(0,120);
   g3->GetYaxis()->SetTitle("E [GeV]");
   g3->SetMinimum(0);
   g3->SetMaximum(5);
   g3->Draw("AP");

   TLine *l3 = new TLine(0,1,120,1);
   l3->Draw();
   cvEv3->cd(1);
   cvEv3->SaveAs("Prob2C.pdf");


   //***************Separación de la distribución lateral para el evento más interesante****************//
   N = 198; //El evento más intersante es este.
   arbol->GetEntry(N);

   auto cv = new TCanvas("cb","Prob2",600,500);
   std::cout << "El evento " << N << " tiene " << nWHit << " hits" << std::endl;
   std::cout << "" << std::endl;

   auto mg = new TMultiGraph();
   auto gr1 = new TGraph(); gr1->SetMarkerColor(4); gr1->SetMarkerSize(0.8); gr1->SetMarkerStyle(20);
   auto gr2 = new TGraph(); gr2->SetMarkerColor(2); gr2->SetMarkerSize(0.8); gr2->SetMarkerStyle(34);
   auto gr3 = new TGraph(); gr3->SetMarkerColor(3); gr3->SetMarkerSize(0.8); gr3->SetMarkerStyle(22);
   //Las partículas más abundantes son las que tienen identificadores 1, 2 y 3
   for(int i=0; i<nWHit; i++){
      //Particula con identificador 1.
       if(WH_pType[i]==1){
        gr1->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
       }
      //Particula con identificador 2.
       if(WH_pType[i]==2){
        gr2->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
       }
      //Particula con identificador 3.
       if(WH_pType[i]==3){
        gr3->SetPoint(i,TMath::Sqrt( TMath::Power(CoreX-XNE[i],2) + TMath::Power(CoreY-YNE[i],2) )/100,WH_Energy[i]);
       }
   }
  
   mg->SetTitle("Distribuci#acute{o}n lateral de las tres part#acute{i}culas m#acute{a}s abundantes. Evento no. 198");
   mg->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   mg->GetXaxis()->SetLimits(0,120);
   mg->GetYaxis()->SetTitle("E [GeV]");
   mg->SetMinimum(0);
   mg->SetMaximum(5);
   mg->Add(gr1,"P");
   mg->Add(gr2,"P");
   mg->Add(gr3,"P");
   mg->Draw("A");

   auto legend = new TLegend(0.7,0.6,0.9,0.9); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("Particle ID","C");
    legend->AddEntry(gr1,"1. #gamma");
    legend->AddEntry(gr2,"2. e^{+}");
    legend->AddEntry(gr3,"3. e^{-}");
    legend->Draw();
    
  cv->cd(1);
  cv->SaveAs("Prob2D.pdf");

}