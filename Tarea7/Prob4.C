#include <iostream>
#include <vector> 
#include <string>
#include <TMath.h>
//Gráfica por evento.

void Prob4(){
    TFile *file = TFile::Open("recoext_run010222_00692.root");
    TTree *arbol = (TTree*) file -> Get("XCDF");

    Double_t charge[1860]; //Carga efectiva
    arbol->SetBranchAddress("event.hit.effcharge",charge);

    Double_t coreX, coreY;  //Posición del núcleo de la cascada
    arbol->SetBranchAddress("rec.coreX",&coreX); arbol->SetBranchAddress("rec.coreY", &coreY);

    Double_t xPMT[1860];   //Posición en x de los PMT de gridID
    Double_t yPMT[1860];   //Posición en y de los PMT de gridID
     arbol->SetBranchAddress("event.hit.xPMT",xPMT); arbol->SetBranchAddress("event.hit.yPMT", yPMT);

    ULong64_t nHit; //Número de hits en el evento
    arbol->SetBranchAddress("event.nHit",&nHit); // Número de hits en el evento.

    ULong64_t channelIsGood[1860];  //Calidad de la señal de los PMT, 1 significa buena señal.
    arbol->SetBranchAddress("event.hit.channelIsGood", channelIsGood); 

    ULong64_t coreFitStatus; //Calidad del ajuste de reconstrucción del núcleo, 0 significa buen ajuste.
    arbol->SetBranchAddress("rec.coreFitStatus", &coreFitStatus);

    ULong64_t isSelected[1860];
    arbol->SetBranchAddress("stdCuts.isSelected", isSelected);
 
    Int_t entradas = arbol->GetEntries();
    
    
    Int_t N = 10; //Este evento es mediano
    arbol->GetEntry(N); 
    std::cout << "El evento " << N << " tiene " << nHit << " hits" << std::endl;
    std::cout << "" << std::endl;
    std::string NoEntrada = to_string(N);
    char NoEntradaChar[50];
    strcpy(NoEntradaChar, NoEntrada.c_str());
    char Tit1[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit1,NoEntradaChar);

    auto cvEv1 = new TCanvas("cb","Prob4",700,500);
    Int_t n = nHit;
    auto gr = new TGraphErrors();  gr->SetMarkerColor(8); gr->SetMarkerSize(0.6); gr->SetMarkerStyle(8);
    for(int i=0; i<nHit; i++){
        if (channelIsGood[i]==1 && isSelected[i] == 1){
            gr->SetPoint(i,TMath::Sqrt( TMath::Power(coreX-xPMT[i],2) + TMath::Power(coreY-yPMT[i],2) ),log10(charge[i]));
            gr->SetPointError(i,0,0.3 - 0.0667*log10(charge[i]));
        }
   }

   //La incertidumbre está dada por 0.3 - 0.0667log(Q_eff)
   gr->SetTitle(Tit1);
   gr->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   gr->GetXaxis()->SetLimits(0,140);
   gr->GetYaxis()->SetTitle("log_{10}(q_{eff})");
   gr->SetMinimum(-1);
   gr->SetMaximum(4);
   gr->Draw("AP");
   
   //Texto
   TPaveText *pt = new TPaveText(40, 2.7, 150, 4); //xini, yini, xfin, yfin. No están normalizadas las coordenadas
   pt->AddText("Se eligen eventos tales que stdCuts.isSelected sea igual a 1 para que satisfaga cortes standard"); 
   pt->AddText("y que los hits sean de buena se#tilde{n}al, i.e. que la variable channelIsGood sea uno.");
   pt->Draw();

  //Función que vamos a ajustar.
   TF1 *f1 = new TF1("f1","[0]*exp([1]*x)",10,110);
   f1->SetParNames("a","b");
   f1->SetParameters(3.3,-0.03);
   //Para hacer ajustes de un sólo parámetro escribimos f1->SetParameters(0,Valor del parámetro)

   gr->Fit("f1","E","",0,120);
   TF1 *fitResult = gr->GetFunction("f1");
   std::cout << "Para una funcion de la forma a*exp(b x), los parametros que mejor se ajustan son" << std::endl;
   std::cout << "a = " << fitResult->GetParameter(0) << std::endl;
   std::cout << "b = " << fitResult->GetParameter(1) << std::endl;
   std::cout << "" << std::endl;
   f1->Draw("Same");
   cvEv1->cd(1);
   cvEv1->SaveAs("Prob4A.pdf");


    //evento pequeño
    N = 724; 
    arbol->GetEntry(N); 
    std::cout << "El evento " << N << " tiene " << nHit << " hits" << std::endl;
    std::cout << "" << std::endl;

    std::string NoEntrada2 = to_string(N);
    char NoEntradaChar2[50];
    strcpy(NoEntradaChar2, NoEntrada2.c_str());
    char Tit2[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit2,NoEntradaChar2);

    auto cvEv2 = new TCanvas("cb2","Prob4",700,500);
    n = nHit;
    auto gr2 = new TGraphErrors();  gr2->SetMarkerColor(8); gr2->SetMarkerSize(0.6); gr2->SetMarkerStyle(8);
    for(int i=0; i<nHit; i++){
        if (channelIsGood[i]==1 && isSelected[i] == 1){
            gr2->SetPoint(i,TMath::Sqrt( TMath::Power(coreX-xPMT[i],2) + TMath::Power(coreY-yPMT[i],2) ),log10(charge[i]));
            gr2->SetPointError(i,0,0.3 - 0.0667*log10(charge[i]));
        }
   }

   //La incertidumbre está dada por 0.3 - 0.0667log(Q_eff)
   gr2->SetTitle(Tit2);
   gr2->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   gr2->GetXaxis()->SetLimits(0,140);
   gr2->GetYaxis()->SetTitle("log_{10}(q_{eff})");
   gr2->SetMinimum(-1);
   gr2->SetMaximum(4);
   gr2->Draw("AP");
   
   //Texto
   TPaveText *pt2 = new TPaveText(40, 2.7, 150, 4); //xini, yini, xfin, yfin. No están normalizadas las coordenadas
   pt2->AddText("Se eligen eventos tales que stdCuts.isSelected sea igual a 1 para que satisfaga cortes standard"); 
   pt2->AddText("y que los hits sean de buena se#tilde{n}al, i.e. que la variable channelIsGood sea uno.");
   pt2->Draw();

  //Función que vamos a ajustar.
   TF1 *f2 = new TF1("f2","[0]*exp([1]*x)",10,110);
   f2->SetParNames("a","b");
   f2->SetParameters(3.3,-0.03);
   //Para hacer ajustes de un sólo parámetro escribimos f1->SetParameters(0,Valor del parámetro)

   gr2->Fit("f2","E","",0,135);
   fitResult = gr2->GetFunction("f2");
   std::cout << "Para una funcion de la forma a*exp(b x), los parametros que mejor se ajustan son" << std::endl;
   std::cout << "a = " << fitResult->GetParameter(0) << std::endl;
   std::cout << "b = " << fitResult->GetParameter(1) << std::endl;
   std::cout << "" << std::endl;
   f2->Draw("Same");
   cvEv2->cd(1);
   cvEv2->SaveAs("Prob4B.pdf");



    //evento grande
    N = 3; 
    arbol->GetEntry(N); 
    std::cout << "El evento " << N << " tiene " << nHit << " hits" << std::endl;
    std::cout << "" << std::endl;

    std::string NoEntrada3 = to_string(N);
    char NoEntradaChar3[50];
    strcpy(NoEntradaChar3, NoEntrada3.c_str());
    char Tit3[ ] = "Distribuci#acute{o}n lateral evento ";
    strcat(Tit3,NoEntradaChar3);

    auto cvEv3 = new TCanvas("cb3","Prob4",700,500);
    n = nHit;
    auto gr3 = new TGraphErrors();  gr3->SetMarkerColor(8); gr3->SetMarkerSize(0.6); gr3->SetMarkerStyle(8);
    for(int i=0; i<nHit; i++){
        if (channelIsGood[i]==1 && isSelected[i] == 1){
            gr3->SetPoint(i,TMath::Sqrt( TMath::Power(coreX-xPMT[i],2) + TMath::Power(coreY-yPMT[i],2) ),log10(charge[i]));
            gr3->SetPointError(i,0,0.3 - 0.0667*log10(charge[i]));
        }
   }

   //La incertidumbre está dada por 0.3 - 0.0667log(Q_eff)
   gr3->SetTitle(Tit3);
   gr3->GetXaxis()->SetTitle("Distancia al n#acute{u}cleo de la cascada [m]");
   gr3->GetXaxis()->SetLimits(0,210);
   gr3->GetYaxis()->SetTitle("log_{10}(q_{eff})");
   gr3->SetMinimum(-1);
   gr3->SetMaximum(4);
   gr3->Draw("AP");
   
   //Texto
   TPaveText *pt3 = new TPaveText(40, 2.7, 150, 4); //xini, yini, xfin, yfin. No están normalizadas las coordenadas
   pt3->AddText("Se eligen eventos tales que stdCuts.isSelected sea igual a 1 para que satisfaga cortes standard"); 
   pt3->AddText("y que los hits sean de buena se#tilde{n}al, i.e. que la variable channelIsGood sea uno.");
   pt3->Draw();

  //Función que vamos a ajustar.
   TF1 *f3 = new TF1("f3","[0]*exp([1]*x)",10,110);
   f3->SetParNames("a","b");
   f3->SetParameters(3.3,-0.03);
   //Para hacer ajustes de un sólo parámetro escribimos f1->SetParameters(0,Valor del parámetro)

   gr3->Fit("f3","E","",20,200);
   fitResult = gr3->GetFunction("f3");
   std::cout << "Para una funcion de la forma a*exp(b x), los parametros que mejor se ajustan son" << std::endl;
   std::cout << "a = " << fitResult->GetParameter(0) << std::endl;
   std::cout << "b = " << fitResult->GetParameter(1) << std::endl;
   std::cout << "" << std::endl;
   f3->Draw("Same");
   cvEv3->cd(1);
   cvEv3->SaveAs("Prob4C.pdf");
/*
for(int i =0; i<entradas; i++){
    arbol->GetEntry(i);
    if (nHit>1240){std::cout << i << std::endl;}
}
*/

   
}
