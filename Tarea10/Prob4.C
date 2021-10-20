#include <iostream>
#include <TMath.h>

void Prob4(){

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


auto cv1 = new TCanvas("cb1","hist1",850,550);
TH1D *h1 = new TH1D("m_{0}","Masa invariante eventos con pares #mu^{-}-#mu^{+}; m_{0} [GeV/c^{2}]; Cuentas",100,0,120); 

Float_t m0;  
Float_t Ptot; //Momento total al cuadrado.
for(int i=0; i<maxrows; i++){
    if (Q1[i] < 0 && Q2[i] > 0){ 
        Ptot = TMath::Power(Px1[i] + Px2[i],2) + TMath::Power(Py1[i] + Py2[i],2) + TMath::Power(Pz1[i] + Pz2[i],2);
        m0 = TMath::Sqrt( TMath::Power(E1[i]+E2[i],2) - Ptot  );
        //std::cout << "Yo calculo m0 = " << m0 << ", los datos dicen que m0 = " << M[i] << std::endl;
        h1->Fill(m0);
    }
    else if(Q1[i] > 0 && Q2[i] < 0){
        Ptot = TMath::Power(Px1[i] + Px2[i],2) + TMath::Power(Py1[i] + Py2[i],2) + TMath::Power(Pz1[i] + Pz2[i],2);
        m0 = TMath::Sqrt( TMath::Power(E1[i]+E2[i],2) - Ptot  );
        h1->Fill(m0);
    }
}

h1->SetFillColorAlpha(kAzure+1,1);
//h1->SetStats(1);
h1->SetLineColor(kAzure+1);
h1->Draw();
cv1->SaveAs("Prob4A.pdf");


//****************************//
auto cv2 = new TCanvas("cb2","hist1",850,550);
TH1D *h2 = new TH1D("m_{0}","Masa invariante eventos con pares #mu^{-}-#mu^{+}; m_{0} [GeV/c^{2}]; Cuentas",100,0,10); 



for(int i=0; i<maxrows; i++){
    if (Q1[i] < 0 && Q2[i] > 0){ 
        Ptot = TMath::Power(Px1[i] + Px2[i],2) + TMath::Power(Py1[i] + Py2[i],2) + TMath::Power(Pz1[i] + Pz2[i],2);
        m0 = TMath::Sqrt( TMath::Power(E1[i]+E2[i],2) - Ptot  );
        //std::cout << "Yo calculo m0 = " << m0 << ", los datos dicen que m0 = " << M[i] << std::endl;
        h2->Fill(m0);
    }
    else if(Q1[i] > 0 && Q2[i] < 0){
        Ptot = TMath::Power(Px1[i] + Px2[i],2) + TMath::Power(Py1[i] + Py2[i],2) + TMath::Power(Pz1[i] + Pz2[i],2);
        m0 = TMath::Sqrt( TMath::Power(E1[i]+E2[i],2) - Ptot  );
        h2->Fill(m0);
    }
}

h2->SetFillColorAlpha(kAzure+1,1);
h2->SetLineColor(kAzure+1);
h2->Draw();
cv2->SaveAs("Prob4B.pdf");

}