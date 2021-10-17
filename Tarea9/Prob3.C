#include <iostream>
#include <cmath>

//Revisar si la correlación es lineal. Los ejes deberían decir 10^1, 10^2, 10^3, etc...
void Prob3(){
    TFile *fileg = TFile::Open("gamma.root"); //Fotones
   // TFile *filep = TFile::Open("protons.root"); //Protones
    TTree *arbolg = (TTree*) fileg -> Get("XCDF");
   // TTree *arbolp =  (TTree*) filep -> Get("XCDF");
    Int_t entradas_g = arbolg->GetEntries();

    //*******Fotones*******//
    Double_t  Esim_G; arbolg->SetBranchAddress("SimEvent.energyTrue",&Esim_G); //Energía simulada GeV
    Double_t  logERN_G; arbolg->SetBranchAddress("rec.logNNEnergyV2",&logERN_G); //Energía reconstruida logaritmo base 10, red neuronal
    Double_t  logEGP_G; arbolg->SetBranchAddress("rec.logGPV2",&logEGP_G); //Energía reconstruida logaritmo base 10, ground parameter.

    //Energía reconstruida red neuronal
    auto cv = new TCanvas("cb","hist",750,550);
    TH2D *h = new TH2D("Energ#acute{i}a #gamma", "Energ#acute{i}a simulada vs. energ#acute{i}a reconstruida, red neuronal; log_{10}(E_{sim}) [GeV]; log_{10}(E_{rec}) [GeV]",100,0,6,100,2,5); 
    for(int i=0; i<entradas_g; i++){
        arbolg->GetEntry(i);
        h->Fill(log10(Esim_G),logERN_G);//Graficamos en escala logarítmica.
    }
    h->SetContour(50);

    TAxis *a = h->GetXaxis();
    a->SetTitle("E_{sim} [GeV]");
    a->SetNdivisions(7,0,0);
    a->ChangeLabel(2,-1,-1,-1,-1,-1,"10^{1}");
    a->ChangeLabel(3,-1,-1,-1,-1,-1,"10^{2}");
    a->ChangeLabel(4,-1,-1,-1,-1,-1,"10^{3}");
    a->ChangeLabel(5,-1,-1,-1,-1,-1,"10^{4}");
    a->ChangeLabel(6,-1,-1,-1,-1,-1,"10^{5}");
    a->ChangeLabel(7,-1,-1,-1,-1,-1,"10^{6}");


    TAxis *b = h->GetYaxis();
    b->SetTitle("E_{rec} [GeV]");
    b->SetNdivisions(4,0,0);
    b->ChangeLabel(1,-1,-1,-1,-1,-1,"10^{2}");
    b->ChangeLabel(2,-1,-1,-1,-1,-1,"10^{3}");
    b->ChangeLabel(3,-1,-1,-1,-1,-1,"10^{4}");
    b->ChangeLabel(4,-1,-1,-1,-1,-1,"10^{5}");

    h->Draw("colz");
    a->Draw("Same");
    b->Draw("Same");

  //Ajuste lineal
   TF1 *f1 = new TF1("f1","[0]+[1]*x",0,6);
   f1->SetParNames("a","b");
   f1->SetParameters(1,1);

   h->Fit("f1","E","",0,6);
   TF1 *fitResult = h->GetFunction("f1");
   std::cout << "Para una funcion de la forma a*exp(b x), los parametros que mejor se ajustan son" << std::endl;
   std::cout << "a = " << fitResult->GetParameter(0) << std::endl;
   std::cout << "b = " << fitResult->GetParameter(1) << std::endl;
   std::cout << "" << std::endl;
   f1->Draw("Same");
   cv->cd(1);

   gPad->Update();
   TPaveStats *st = (TPaveStats*) h->FindObject("stats");
   //gPad->SetLogx(1);
   gPad->Modified();
   st->SetX1NDC(0.1);
   st->SetX2NDC(0.3);
   st->SetY1NDC(0.7);
   st->SetY2NDC(0.9);
   cv->cd(1);
   cv->SaveAs("Prob3A.pdf");


    //Energía reconstruida red neuronal
    auto cv2 = new TCanvas("cb2","hist2",750,550);
    TH2D *h2 = new TH2D("Energ#acute{i}a #gamma", "Energ#acute{i}a simulada vs. energ#acute{i}a reconstruida, ground parameter; log_{10}(E_{sim}) [log_{10}(GeV)]; log_{10}(E_{rec}) [log_{10}(GeV)]",100,0,6,100,0,6); 
    for(int i=0; i<entradas_g; i++){
        arbolg->GetEntry(i);
        h2->Fill(log10(Esim_G),logEGP_G);
    }
    h2->SetContour(50);
    a = h2->GetXaxis();
    a->SetTitle("E_{sim} [GeV]");
    a->SetNdivisions(7,0,0);
    a->ChangeLabel(2,-1,-1,-1,-1,-1,"10^{1}");
    a->ChangeLabel(3,-1,-1,-1,-1,-1,"10^{2}");
    a->ChangeLabel(4,-1,-1,-1,-1,-1,"10^{3}");
    a->ChangeLabel(5,-1,-1,-1,-1,-1,"10^{4}");
    a->ChangeLabel(6,-1,-1,-1,-1,-1,"10^{5}");
    a->ChangeLabel(7,-1,-1,-1,-1,-1,"10^{6}");


    b = h2->GetYaxis();
    b->SetTitle("E_{rec} [GeV]");
    b->SetNdivisions(7,0,0);
    b->ChangeLabel(2,-1,-1,-1,-1,-1,"10^{1}");
    b->ChangeLabel(3,-1,-1,-1,-1,-1,"10^{2}");
    b->ChangeLabel(4,-1,-1,-1,-1,-1,"10^{3}");
    b->ChangeLabel(5,-1,-1,-1,-1,-1,"10^{4}");
    b->ChangeLabel(6,-1,-1,-1,-1,-1,"10^{5}");
    b->ChangeLabel(7,-1,-1,-1,-1,-1,"10^{6}");



    h2->Draw("colz");

    gPad->Update();
    TPaveStats *st2 = (TPaveStats*) h2->FindObject("stats");
    gPad->Modified();
    st2->SetX1NDC(0.1);
    st2->SetX2NDC(0.3);
    st2->SetY1NDC(0.7);
    st2->SetY2NDC(0.9);

    //Ajuste lineal
   TF1 *f2 = new TF1("f2","[0]+[1]*x",0,6);
   f2->SetParNames("a","b");
   f2->SetParameters(1,1);

   h2->Fit("f2","E","",0,6);
   TF1 *fitResult2 = h2->GetFunction("f2");
   std::cout << "Para una funcion de la forma a*exp(b x), los parametros que mejor se ajustan son" << std::endl;
   std::cout << "a = " << fitResult2->GetParameter(0) << std::endl;
   std::cout << "b = " << fitResult2->GetParameter(1) << std::endl;
   std::cout << "" << std::endl;
   f2->Draw("Same");
   cv2->cd(1);
   cv2->SaveAs("Prob3B.pdf");


}

