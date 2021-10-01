#include <iostream>
#include <vector> 
#include <string>
#include <TMath.h>


void Prob2(){
    TFile *file = TFile::Open("recoext_run010222_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");

   //PMT 383 K16C, 1163 X5C,   

    ULong64_t gridID[1860];   //ID de los PMT 
    ULong64_t tankId[1860];   
    Double_t charge[1860]; //La dimensión de estos amiwos es el número de hits en el evento.
    ULong64_t loTOT[1860];   
    ULong64_t  hiTOT[1860];
    ULong64_t nHit; // Número de hits en el evento.
    ULong64_t channelIsGood[1860];//Calidad de la señal
    Double_t loPMT1[6700], loPMT2[6700]; //LowTOT [6700]
    Double_t hiPMT1[6700], hiPMT2[6700];
    Double_t cPMT1[6700], cPMT2[6700]; //Carga calibrada de cada PMT
    
    Int_t entradas = arbol->GetEntries();
    
    arbol->SetBranchAddress("event.hit.tankId", tankId);
    arbol->SetBranchAddress("event.hit.charge",charge);
    arbol->SetBranchAddress("event.hit.loTOT",loTOT);
    arbol->SetBranchAddress("event.hit.hiTOT", hiTOT);
    arbol->SetBranchAddress("event.hit.channelIsGood", channelIsGood);
    arbol->SetBranchAddress("event.hit.gridId",gridID);
    arbol->SetBranchAddress("event.nHit",&nHit);

    //auto cvEv1 = new TCanvas("cb","Prob1",1500,750); 
    int n1 = 0, n2 = 0;
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        for(int j=0; j<nHit; j++){
          if(channelIsGood[j] == 1 && charge[j]!=0){
            if(gridID[j]==383){ 
                loPMT1[n1] = loTOT[j];
                hiPMT1[n1] = hiTOT[j];
                cPMT1[n1] = log10(charge[j]);
                n1 += 1;
                }
            else if(gridID[j]==1163){
                loPMT2[n2] = loTOT[j];
                hiPMT2[n2] = hiTOT[j];
                cPMT2[n2] = log10(charge[j]);
                n2 += 1;
                }
          }
        }
    } 

  //for(int i=0; i<n1; i++){
    //std::cout << cPMT1[i] << std::endl;
  //}
  
        
  auto c1 = new TCanvas("cb","Prob1",600,500);
  auto mg = new TMultiGraph();
   
   auto gr = new TGraph();  gr->SetMarkerColor(4); gr->SetMarkerSize(0.6); gr->SetMarkerStyle(22);
   auto gr2 = new TGraph(); gr2->SetMarkerColor(2); gr2->SetMarkerSize(0.6); gr2->SetMarkerStyle(23);
   for(int i=0; i<n1; i++){
     gr->SetPoint(i,loPMT1[i],cPMT1[i]);
   }
  for(int i=0; i<n2; i++){
     gr2->SetPoint(i,loPMT2[i],cPMT2[i]);
   }
   mg->SetTitle("Curvas de calibraci#acute{o}n");
   mg->GetXaxis()->SetTitle("Low ToT [TDC Counts]");
   mg->GetXaxis()->SetLimits(0,5000);
   mg->GetYaxis()->SetTitle("log_{10}(C)");
   mg->SetMinimum(-0.3);
   mg->SetMaximum(1);
   mg->Add(gr,"P");
   mg->Add(gr2,"P");
   mg->Draw("A");

  auto legend = new TLegend(0.1,0.6,0.2,0.8); //TLegend(x1,y1,x2,y2)
  legend->SetHeader("PMD ID","C");
  legend->AddEntry(gr,"383");
  legend->AddEntry(gr2,"1163");
  legend->Draw();
  c1->cd(1);
  c1->SaveAs("Prob2A.pdf");

  auto c2 = new TCanvas("c2","Prob1",600,500);
  auto mg2 = new TMultiGraph();
   
   auto gr12 = new TGraph(); gr12->SetMarkerColor(4); gr12->SetMarkerSize(0.6); gr12->SetMarkerStyle(22);
   auto gr22 = new TGraph(); gr22->SetMarkerColor(2); gr22->SetMarkerSize(0.6); gr22->SetMarkerStyle(23);
   for(int i=0; i<n1; i++){
     gr12->SetPoint(i,hiPMT1[i],log10(cPMT1[i]));
   }
  for(int i=0; i<n2; i++){
     gr22->SetPoint(i,hiPMT2[i],log10(cPMT2[i]));
   }
   mg2->SetTitle("Curvas de calibraci#acute{o}n");
   mg2->GetXaxis()->SetTitle("High ToT [TDC Counts]");
   mg2->GetXaxis()->SetLimits(1,5000);
   mg2->GetYaxis()->SetTitle("log_{10}(q)");
   mg2->SetMinimum(-0.3);
   mg2->SetMaximum(1);
   mg2->Add(gr12,"P");
   mg2->Add(gr22,"P");
   mg2->Draw("A");

   auto legend2 = new TLegend(0.1,0.6,0.2,0.8); //TLegend(x1,y1,x2,y2)
    legend2->SetHeader("PMD ID","C");
    legend2->AddEntry(gr12,"383");
    legend2->AddEntry(gr22,"1163");
    legend2->Draw();
    
  c2->cd(1);
  c2->SaveAs("Prob2B.pdf");
    

}