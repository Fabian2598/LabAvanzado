#include <iostream>

void Prob2(){

TString file = "CMSMuon.txt";
const int maxrows = 100000;
Float_t pi = 3.14159265359;

Float_t Run[maxrows],Event[maxrows], E1[maxrows], Px1[maxrows], Px2[maxrows],
Py1[maxrows], Py2[maxrows],  Pz1[maxrows], Pz2[maxrows], Pt1[maxrows], Pt2[maxrows],
eta1[maxrows], eta2[maxrows], E2[maxrows], phi1[maxrows], phi2[maxrows], M[maxrows],
Q1[maxrows], Q2[maxrows]; 

char Type1[maxrows], Type2[maxrows];

Int_t contador = 0;
std::ifstream infile(file.Data());
while(contador < maxrows){
    infile >> Run[contador] >> Event[contador] >> Type1[contador] >> E1[contador] >> Px1[contador] >> Py1[contador] >> Pz1[contador]
    >> Pt1[contador] >> eta1[contador] >> phi1[contador] >> Q1[contador] >> Type2[contador] >> E2[contador] >> Px2[contador] 
    >> Py2[contador] >> Pz2[contador] >> Pt2[contador] >> eta2[contador] >> phi2[contador] >> Q2[contador] >> M[contador];
    contador ++;
}

//*************Distribución de eta****************//
    auto cv1 = new TCanvas("cb","hist1",700,550);
    TH1D *h1 = new TH1D("#eta","Distribuci#acute{o}n #eta separada por carga; #eta [#circ]; Cuentas",100,-150,150); //Carga positiva
    TH1D *h2 = new TH1D("#eta","Distribuci#acute{o}n #eta separada por carga; #eta [#circ]; Cuentas",100,-150,150); //Carga negativa
    for(int i=0; i<maxrows; i++){
        //Carga positiva
        if (Q1[i]>0){h1->Fill(eta1[i]*180/pi);}
        if (Q2[i]>0){h1->Fill(eta2[i]*180/pi);}

        //Carga negativa
        if(Q1[i]<0){h2->Fill(eta1[i]*180/pi);}
        if(Q2[i]<0){h2->Fill(eta2[i]*180/pi);}
    }
    h1->SetFillColorAlpha(kOrange+1,0.8);
    h1->SetStats(0);
    h1->SetLineColor(kOrange+1);
    h1->SetBarWidth(1);
    h1->GetYaxis()->SetRangeUser(0,2000);
    h1->Draw();

    h2->SetFillColorAlpha(kTeal-9,0.6);
    h2->SetStats(0);
    h2->SetLineColor(kTeal-9);
    h2->SetBarWidth(1);
    h2->GetYaxis()->SetRangeUser(0,2000);
    h2->Draw("Same");

    auto legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->SetHeader("Carga");
    legend->AddEntry(h1,"Positiva");
    legend->AddEntry(h2,"Negativa");
    legend->Draw();

    cv1->cd(1);
    cv1->SaveAs("Prob2A.pdf");

//*************Distribución de phi****************//
    auto cv2 = new TCanvas("cb","hist1",700,550);
    TH1D *h3 = new TH1D("#phi","Distribuci#acute{o}n #phi separada por carga; #phi [#circ]; Cuentas",100,-180,180); //Carga positiva
    TH1D *h4 = new TH1D("#phi","Distribuci#acute{o}n #phi separada por carga; #phi [#circ]; Cuentas",100,-180,180); //Carga negativa
    for(int i=0; i<maxrows; i++){
        //Carga positiva
        if (Q1[i]>0){h3->Fill(phi1[i]*180/pi);}
        if (Q2[i]>0){h3->Fill(phi2[i]*180/pi);}

        //Carga negativa
        if(Q1[i]<0){h4->Fill(phi1[i]*180/pi);}
        if(Q2[i]<0){h4->Fill(phi2[i]*180/pi);}
    }
    h3->SetFillColorAlpha(kOrange+1,0.8);
    h3->SetStats(0);
    h3->SetLineColor(kOrange+1);
    h3->SetBarWidth(1);
    h3->GetYaxis()->SetRangeUser(0,2000);
    h3->Draw();

    h4->SetFillColorAlpha(kTeal-9,0.6);
    h4->SetStats(0);
    h4->SetLineColor(kTeal-9);
    h4->SetBarWidth(1);
    h4->GetYaxis()->SetRangeUser(0,2000);
    h4->Draw("Same");

    auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
    legend2->SetHeader("Carga");
    legend2->AddEntry(h3,"Positiva");
    legend2->AddEntry(h4,"Negativa");
    legend2->Draw();

    cv2->cd(1);
    cv2->SaveAs("Prob2B.pdf");
}
