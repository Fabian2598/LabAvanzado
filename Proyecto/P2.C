#include <iostream>

//Histogramas de la signficancia de cada bin (Punto 2).
void P2(){

const long int maxrows = 12*256*256; //Número de elementos de cada archivo.
Float_t pi = 3.14159265359;

Double_t AR, Dec, Sig; 

const char *Nombres[10] = {"luna_protonlhe/tabla_0.dat", "luna_protonlhe/tabla_1.dat", "luna_protonlhe/tabla_2.dat",
"luna_protonlhe/tabla_3.dat", "luna_protonlhe/tabla_4.dat", "luna_protonlhe/tabla_5.dat",
"luna_protonlhe/tabla_6.dat","luna_protonlhe/tabla_7.dat","luna_protonlhe/tabla_8.dat",
"luna_protonlhe/tabla_9.dat"};

auto cv1 = new TCanvas("cb","hist1",850,550);
TH1D *h0 = new TH1D("bin0","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h1 = new TH1D("bin1","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h2 = new TH1D("bin2","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h3 = new TH1D("bin3","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h4 = new TH1D("bin4","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h5 = new TH1D("bin5","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h6 = new TH1D("bin6","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h7 = new TH1D("bin7","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h8 = new TH1D("bin8","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 
TH1D *h9 = new TH1D("bin9","Significancia por cada bin; Significancia; Cuentas",100,-10,10); 

TString file; 
Int_t contador;

for(int i=0; i<10; i++ ){
    file = Nombres[i];
    std::ifstream infile(file.Data());
    contador = 0;
    while(contador < maxrows){
        infile >> AR >> Dec >> Sig;
        if (i==0){h0->Fill(Sig);}
        if (i==1){h1->Fill(Sig);}
        if (i==2){h2->Fill(Sig);}
        if (i==3){h3->Fill(Sig);}
        if (i==4){h4->Fill(Sig);}
        if (i==5){h5->Fill(Sig);}
        if (i==6){h6->Fill(Sig);}
        if (i==7){h7->Fill(Sig);}
        if (i==8){h8->Fill(Sig);}
        if (i==9){h9->Fill(Sig);}
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
    cv1->SaveAs("Punto2A.pdf");   
}