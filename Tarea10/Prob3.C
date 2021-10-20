#include <iostream>

void Prob3(){

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

    auto cv1 = new TCanvas("cb","hist1",850,550);
    TH1D *h1 = new TH1D("pt","Momento transverso; P_{t} [GeV]; Cuentas",100,0,35); 
    TH1D *h2 = new TH1D("pt2","Momento transverso muones positivos; P_{t} [GeV]; Cuentas",100,0,35); //Carga positiva
    TH1D *h3 = new TH1D("pt3","Momento transverso muones negativos; P_{t} [GeV]; Cuentas",100,0,35); //Carga negativa
    for(int i=0; i<maxrows; i++){
        h1->Fill(Pt1[i]);
        h1->Fill(Pt2[i]);
        //Carga positiva
        if (Q1[i]>0){h2->Fill(Pt1[i]);}
        if (Q2[i]>0){h2->Fill(Pt2[i]);}

        //Carga negativa
        if(Q1[i]<0){h3->Fill(Pt1[i]);}
        if(Q2[i]<0){h3->Fill(Pt2[i]);}
    }
    h1->SetFillColorAlpha(kAzure,0.5);
    h1->SetStats(0);
    h1->SetLineColor(kAzure);
    h1->SetBarWidth(1);
   // h1->GetYaxis()->SetRangeUser(0,2000);
    h1->Draw();

    h2->SetFillColorAlpha(kRed,0.5);
    h2->SetStats(0);
    h2->SetLineColor(kRed);
    h2->SetBarWidth(1);
    //h2->GetYaxis()->SetRangeUser(0,2000);
    h2->Draw("Same");

    h3->SetFillColorAlpha(kGreen-7,0.2);
    h3->SetStats(0);
    h3->SetLineColor(kGreen-7);
    h3->SetBarWidth(1);
    //h3->GetYaxis()->SetRangeUser(0,2000);
    h3->Draw("Same");

    auto legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->SetHeader("Muones");
    legend->AddEntry(h1,"Todos");
    legend->AddEntry(h2,"Positiva");
    legend->AddEntry(h3,"Negativa");
    legend->Draw();

    cv1->cd(1);
    cv1->SaveAs("Prob3.pdf");

}