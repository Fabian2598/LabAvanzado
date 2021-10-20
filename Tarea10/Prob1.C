#include <iostream>

void Prob1(){

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
/*
for(int i=0; i<10; i++){
    std::cout << Run[i] << " " << Event[i] << " " << Type1[i] << " " << E1[i] << " " << Px1[i] << 
    " " << Py1[i]<< " " << Pz1[i] << " " << Pt1[i] << " " << eta1[i] << " " << phi1[i] << " " << Q1[i] 
    << " " << Type2[i] << " " << E2[i] << " " << Px2[i] << 
    " " << Py2[i]<< " " << Pz2[i] << " " << Pt2[i] << " " << eta2[i] << " " << phi2[i] << " " << Q2[i] 
    << " " << M[i] << std::endl;
}
*/

//*************Distribución de eta****************//
    auto cv1 = new TCanvas("cb","hist1",700,550);
    TH1D *h1 = new TH1D("#eta","Distribuci#acute{o}n #eta; #eta [#circ]; Cuentas",100,-150,150); 
    for(int i=0; i<maxrows; i++){
        h1->Fill(eta1[i]*180/pi);
        h1->Fill(eta2[i]*180/pi);
    }
    h1->SetFillColorAlpha(9,0.6);
    h1->SetLineColor(9);
    h1->SetBarWidth(1);
    h1->GetYaxis()->SetRangeUser(0,4000);
    h1->Draw();
    gPad->Update();
    TPaveStats *st = (TPaveStats*) h1->FindObject("stats");
    gPad->Modified();
    st->SetX1NDC(0.1);
    st->SetX2NDC(0.3);
    st->SetY1NDC(0.8);
    st->SetY2NDC(1);

    cv1->cd(1);
    cv1->SaveAs("Prob1A.pdf");

//*************Distribución de phi****************//
    auto cv2 = new TCanvas("cb2","hist2",700,550);
    TH1D *h2 = new TH1D("#phi","Distribuci#acute{o}n #phi; #phi [#circ]; Cuentas",100,-180,180); 
    for(int i=0; i<maxrows; i++){
        h2->Fill(phi1[i]*180/pi);
        h2->Fill(phi2[i]*180/pi);
    }
    h2->SetFillColorAlpha(kViolet+1,0.6);
    h2->SetLineColor(kViolet+1);
    h2->SetBarWidth(1);
    h2->GetYaxis()->SetRangeUser(0,2500);
    h2->Draw();

    gPad->Update();
    TPaveStats *st2 = (TPaveStats*) h2->FindObject("stats");
    gPad->Modified();
    st2->SetX1NDC(0.1);
    st2->SetX2NDC(0.3);
    st2->SetY1NDC(0.8);
    st2->SetY2NDC(1);

    cv2->cd(1);
    cv2->SaveAs("Prob1B.pdf");

}
