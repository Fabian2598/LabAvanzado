#include <iostream>
#include <vector> 
#include <string>
#include <TMath.h>

/* Tanque 96 --> Con este vamos a trabajar.
<tank id="96">
      <name> K16 </name>
      <type> 1 </type>
      <position>
        <x unit="cm"> 5567.75 </x>
        <y unit="cm"> 28550.46 </y>
        <z unit="cm"> -2.87 </z>
      </position>
      <channels>
        <channel id="381">
          <name> K16A </name>
          <number> 1 </number>
          <type> 1 </type>
          <position>
            <x unit="cm"> 132.11 </x>
            <y unit="cm"> -129.44 </y>
            <z unit="cm"> 29.52 </z>
          </position>
        </channel>
        <channel id="382">
          <name> K16B </name>
          <number> 2 </number>
          <type> 1 </type>
          <position>
            <x unit="cm"> -178.47 </x>
            <y unit="cm"> -49.84 </y>
            <z unit="cm"> 31.40 </z>
          </position>
        </channel>
        <channel id="383">
          <name> K16C </name>
          <number> 3 </number>
          <type> 2 </type>
          <position>
            <x unit="cm"> 0.00 </x>
            <y unit="cm"> 0.00 </y>
            <z unit="cm"> 33.87 </z>
          </position>
        </channel>
        <channel id="384">
          <name> K16D </name>
          <number> 4 </number>
          <type> 1 </type>
          <position>
            <x unit="cm"> 46.43 </x>
            <y unit="cm"> 178.67 </y>
            <z unit="cm"> 31.41 </z>
          </position>
        </channel>
      </channels>
    </tank>
*/


void Prob1(){
    TFile *file = TFile::Open("recoext_run010222_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");

    int Tank = 96; //PMT 381, 382, 383 y 384

    ULong64_t gridID[1860];   //ID de los PMT 
    ULong64_t tankId[1860];   
    Double_t charge[1860]; 
    ULong64_t loTOT[1860];   
    ULong64_t  hiTOT[1860];
    ULong64_t nHit; // Número de hits en el evento.
    ULong64_t channelIsGood[1860];//Calidad de la señal
    Double_t loPMT1[6700], loPMT2[6700], loPMT3[6700], loPMT4[6700]; //LowTOT [6700]
    Double_t hiPMT1[6700], hiPMT2[6700], hiPMT3[6700], hiPMT4[6700];
    Double_t cPMT1[6700], cPMT2[6700], cPMT3[6700], cPMT4[6700]; //Carga calibrada de cada PMT
    
    Int_t entradas = arbol->GetEntries();
    
    arbol->SetBranchAddress("event.hit.tankId", tankId);
    arbol->SetBranchAddress("event.hit.charge",charge);
    arbol->SetBranchAddress("event.hit.loTOT",loTOT);
    arbol->SetBranchAddress("event.hit.hiTOT", hiTOT);
    arbol->SetBranchAddress("event.hit.channelIsGood", channelIsGood);
    arbol->SetBranchAddress("event.hit.gridId",gridID);
    arbol->SetBranchAddress("event.nHit",&nHit);

    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    for(int i=0; i<entradas; i++){
        arbol->GetEntry(i);
        for(int j=0; j<nHit; j++){
          if(channelIsGood[j] == 1 && charge[j]!=0){
            if(gridID[j]==381){ 
                loPMT1[n1] = loTOT[j];
                hiPMT1[n1] = hiTOT[j];
                cPMT1[n1] = (charge[j]);
                n1 += 1;
                }
            else if(gridID[j]==382){
                loPMT2[n2] = loTOT[j];
                hiPMT2[n2] = hiTOT[j];
                cPMT2[n2] = (charge[j]);
                n2 += 1;
                }
            else if(gridID[j]==383){
                loPMT3[n3] = loTOT[j];
                hiPMT3[n3] = hiTOT[j];
                cPMT3[n3] = (charge[j]);
                n3 += 1;
                }
            else if(gridID[j]==384){
                loPMT4[n4] = loTOT[j];
                hiPMT4[n4] = hiTOT[j];
                cPMT4[n4] = (charge[j]);
                n4 += 1;
                }
          }
        }
    } 

  //for(int i=0; i<n4; i++){
   //   std::cout << cPMT4[i] << std::endl;
 // }
  
        
  auto c1 = new TCanvas("cb","Prob1",600,500);
  auto mg = new TMultiGraph();
   
   auto gr = new TGraph();  gr->SetMarkerColor(4); gr->SetMarkerSize(0.6); gr->SetMarkerStyle(22);
   auto gr2 = new TGraph(); gr2->SetMarkerColor(2); gr2->SetMarkerSize(0.6); gr2->SetMarkerStyle(23);
   auto gr3 = new TGraph(); gr3->SetMarkerColor(3); gr3->SetMarkerSize(0.6); gr3->SetMarkerStyle(3);
   auto gr4 = new TGraph(); gr4->SetMarkerColor(1); gr4->SetMarkerSize(0.6); gr4->SetMarkerStyle(29);
   for(int i=0; i<n1; i++){
     gr->SetPoint(i,loPMT1[i],log10(cPMT1[i]));
   }
  for(int i=0; i<n2; i++){
     gr2->SetPoint(i,loPMT2[i],log10(cPMT2[i]));
   }
  for(int i=0; i<n3; i++){
     gr3->SetPoint(i,loPMT3[i],log10(cPMT3[i]));
   }
  for(int i=0; i<n4; i++){
     gr4->SetPoint(i,loPMT4[i],log10(cPMT4[i]));
   }
   mg->SetTitle("Tanque 96");
   mg->GetXaxis()->SetTitle("Low ToT [TDC Counts]");
   mg->GetXaxis()->SetLimits(1,5000);
   mg->GetYaxis()->SetTitle("log_{10}(q)");
   mg->SetMinimum(-0.5);
   mg->SetMaximum(5);
   mg->Add(gr,"P");
   mg->Add(gr2,"P");
   mg->Add(gr3,"P");
   mg->Add(gr4,"P");
   mg->Draw("A");

   auto legend = new TLegend(0.1,0.6,0.2,0.8); //TLegend(x1,y1,x2,y2)
    legend->SetHeader("PMD ID","C");
    legend->AddEntry(gr,"381");
    legend->AddEntry(gr2,"382");
    legend->AddEntry(gr3,"383");
    legend->AddEntry(gr4,"384");
    legend->Draw();
    
  c1->cd(1);
  c1->SaveAs("Prob1A.pdf");

  auto c2 = new TCanvas("c2","Prob1",600,500);
  auto mg2 = new TMultiGraph();
   
   auto gr12 = new TGraph(); gr12->SetMarkerColor(4); gr12->SetMarkerSize(0.6); gr12->SetMarkerStyle(22);
   auto gr22 = new TGraph(); gr22->SetMarkerColor(2); gr22->SetMarkerSize(0.6); gr22->SetMarkerStyle(23);
   auto gr32 = new TGraph(); gr32->SetMarkerColor(3); gr32->SetMarkerSize(0.6); gr32->SetMarkerStyle(3);
   auto gr42 = new TGraph(); gr42->SetMarkerColor(1); gr42->SetMarkerSize(0.6); gr42->SetMarkerStyle(29);
   for(int i=0; i<n1; i++){
     gr12->SetPoint(i,hiPMT1[i],log10(cPMT1[i]));
   }
  for(int i=0; i<n2; i++){
     gr22->SetPoint(i,hiPMT2[i],log10(cPMT2[i]));
   }
  for(int i=0; i<n3; i++){
     gr32->SetPoint(i,hiPMT3[i],log10(cPMT3[i]));
   }
  for(int i=0; i<n4; i++){
     gr42->SetPoint(i,hiPMT4[i],log10(cPMT4[i]));
   }
   mg2->SetTitle("Tanque 96");
   mg2->GetXaxis()->SetTitle("High ToT [TDC Counts]");
   mg2->GetXaxis()->SetLimits(1,5000);
   mg2->GetYaxis()->SetTitle("log_{10}(q)");
   mg2->SetMinimum(-0.5);
   mg2->SetMaximum(5);
   mg2->Add(gr12,"P");
   mg2->Add(gr22,"P");
   mg2->Add(gr32,"P");
   mg2->Add(gr42,"P");
   mg2->Draw("A");

   auto legend2 = new TLegend(0.1,0.6,0.2,0.8); //TLegend(x1,y1,x2,y2)
    legend2->SetHeader("PMD ID","C");
    legend2->AddEntry(gr12,"381");
    legend2->AddEntry(gr22,"382");
    legend2->AddEntry(gr32,"383");
    legend2->AddEntry(gr42,"384");
    legend2->Draw();
    
  c2->cd(1);
  c2->SaveAs("Prob1B.pdf");
  
}