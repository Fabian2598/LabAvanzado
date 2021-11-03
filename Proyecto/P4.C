#include <iostream>
#include "TGraph.h"
//Histogramas de la significancia estimador nn (Punto 4 parte uno).
void P4(){

const long int maxrows = 12*256*256-1; //Número de elementos de cada archivo.
Float_t pi = 3.14159265359;

Double_t AR, Dec, Sig; 

const char *Nombres[10] = {"luna_nn/tabla_0.dat", "luna_nn/tabla_1.dat", "luna_nn/tabla_2.dat",
"luna_nn/tabla_3.dat", "luna_nn/tabla_4.dat", "luna_nn/tabla_5.dat",
"luna_nn/tabla_6.dat","luna_nn/tabla_7.dat","luna_nn/tabla_8.dat",
"luna_nn/tabla_9.dat"};


auto cv1 = new TCanvas("cb","hist1",850,550);
TH1D *h0 = new TH1D("bin0","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h1 = new TH1D("bin1","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h2 = new TH1D("bin2","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h3 = new TH1D("bin3","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h4 = new TH1D("bin4","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h5 = new TH1D("bin5","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h6 = new TH1D("bin6","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h7 = new TH1D("bin7","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h8 = new TH1D("bin8","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 
TH1D *h9 = new TH1D("bin9","Significancia por cada bin estimador nn; Significancia; Cuentas",100,-10,10); 

Double_t ARmin[10], Decmin[10], Sigmin[10], bines[10];
TString file; 
Int_t contador;

for(int i=0; i<10; i++ ){
    file = Nombres[i];
    std::ifstream infile(file.Data());
    contador = 0;
    ARmin[i] = 0; Decmin[i] = 0; Sigmin[i] = 0; bines[i] = i;
    while(contador < maxrows){
        infile >> AR >> Dec >> Sig;
        if (i==0){h0->Fill(Sig);if(Sig<Sigmin[0]){Sigmin[0]=Sig; ARmin[0]=AR; Decmin[0]=Dec;}}
        if (i==1){h1->Fill(Sig);if(Sig<Sigmin[1]){Sigmin[1]=Sig; ARmin[1]=AR; Decmin[1]=Dec;}}
        if (i==2){h2->Fill(Sig);if(Sig<Sigmin[2]){Sigmin[2]=Sig; ARmin[2]=AR; Decmin[2]=Dec;}}
        if (i==3){h3->Fill(Sig);if(Sig<Sigmin[3]){Sigmin[3]=Sig; ARmin[3]=AR; Decmin[3]=Dec;}}
        if (i==4){h4->Fill(Sig);if(Sig<Sigmin[4]){Sigmin[4]=Sig; ARmin[4]=AR; Decmin[4]=Dec;}}
        if (i==5){h5->Fill(Sig);if(Sig<Sigmin[5]){Sigmin[5]=Sig; ARmin[5]=AR; Decmin[5]=Dec;}}
        if (i==6){h6->Fill(Sig);if(Sig<Sigmin[6]){Sigmin[6]=Sig; ARmin[6]=AR; Decmin[6]=Dec;}}
        if (i==7){h7->Fill(Sig);if(Sig<Sigmin[7]){Sigmin[7]=Sig; ARmin[7]=AR; Decmin[7]=Dec;}}
        if (i==8){h8->Fill(Sig);if(Sig<Sigmin[8]){Sigmin[8]=Sig; ARmin[8]=AR; Decmin[8]=Dec;}}
        if (i==9){h9->Fill(Sig);if(Sig<Sigmin[9]){Sigmin[9]=Sig; ARmin[9]=AR; Decmin[9]=Dec;}}
    contador ++;
    }
}

    gStyle->SetOptStat(0);

    h0->SetStats(0);
    h0->SetMarkerStyle(kFullCircle);
    h0->SetMarkerSize(1);
    h0->GetYaxis()->SetRangeUser(0,50000); //(0,255000)
    h0->Draw("PMC PLC P");

    h1->SetMarkerStyle(kFullSquare);
    h1->SetStats(0);
    h1->SetMarkerSize(1);
    h1->Draw("SAME PMC PLC P");

    h2->SetMarkerStyle(kFullTriangleUp);
    h2->SetStats(0);
    h2->SetMarkerSize(1);
    h2->Draw("SAME PMC PLC P");

    h3->SetMarkerStyle(kFullTriangleDown);
    h3->SetStats(0);
    h3->SetMarkerSize(1);
    h3->Draw("SAME PMC PLC P");

    h4->SetMarkerStyle(kStar);
    h4->SetStats(0);
    h4->SetMarkerSize(1);
    h4->Draw("SAME PMC PLC P");

    h5->SetMarkerStyle(kFullCross);
    h5->SetStats(0);
    h5->SetMarkerSize(1);
    h5->Draw("SAME PMC PLC P");

    h6->SetMarkerStyle(kPlus);
    h6->SetStats(0);
    h6->SetMarkerSize(1);
    h6->Draw("SAME PMC PLC P");

    h7->SetMarkerStyle(kFullDoubleDiamond);
    h7->SetStats(0);
    h7->SetMarkerSize(1);
    h7->Draw("SAME PMC PLC P");

    h8->SetMarkerStyle(kFullCrossX);
    h8->SetStats(0);
    h8->SetMarkerSize(1);
    h8->Draw("SAME PMC PLC P");

    h9->SetMarkerStyle(kFourSquaresX);
    h9->SetStats(0);
    h9->SetMarkerSize(1);
    h9->Draw("SAME PMC PLC P");

    auto legend = new TLegend(0.6,0.5,0.9,0.9);
    legend->SetHeader("Bin");
    legend->AddEntry(h0,"Bin 0");
    legend->AddEntry(h1,"Bin 1");
    legend->AddEntry(h2,"Bin 2");
    legend->AddEntry(h3,"Bin 3");
    legend->AddEntry(h4,"Bin 4");
    legend->AddEntry(h5,"Bin 5");
    legend->AddEntry(h6,"Bin 6");
    legend->AddEntry(h7,"Bin 7");
    legend->AddEntry(h8,"Bin 8");
    legend->AddEntry(h9,"Bin 9"); 
    legend->Draw();

    cv1->cd(1);
    cv1->SaveAs("Punto4A.pdf");

    double sm=0,am,dm, bin; //Aquí guardamos la significancia mínima, el bin y sus coordenadas. 
    for(int i=0;i<10;i++){
        if(Sigmin[i]<sm){
            sm=Sigmin[i];
            dm=ARmin[i];
            am=Decmin[i];
            bin=i;
        }
    }   

    TCanvas *cs = new TCanvas("cs","canvas");
    cs->SetFillColor(kOrange-9);
    auto gr = new TGraph(10,bines,Sigmin);  gr->SetMarkerColor(kRed); gr->SetMarkerSize(1.5); gr->SetMarkerStyle(47); gr->SetLineColor(kRed);
    gr->SetTitle("Significancia m#acute{i}nima (Neural Network)");
    gr->GetXaxis()->SetTitle("Bin");
    gr->GetYaxis()->SetTitle("Significancia [#sigma]");
    gr->Draw("ALP");
    cs->cd(1);


    cs->Update();
    cs->GetFrame()->SetFillColor(21);
    cs->Modified();
    cout<<"El valor mínimo se encuentra en el bin "<<bin<<" y corresponde a una ascención recta de "<<am<<" y a una declinación de " <<dm<<endl; 
    cout<<"Corresponde a "<<sm<<" sigmas"<<endl;

    cs->SaveAs("Sig_nn.pdf");
}