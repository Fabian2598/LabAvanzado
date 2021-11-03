#include <vector>
#include "TGraph.h"

//Punto cinco del proyecto.
void P5(){
TString file="luna_protonlhe/tabla_1.dat";
const int maxrows = 12*256*256-1; //Número de elementos en las tablas. 
std::ifstream infile(file.Data());

Double_t AR, Dec, Sig; //Ascensión recta, declinación y significancia  
auto cv = new TCanvas("cb","hist1",850,550);
auto *H = new TH2F("ML","Mapa de la Luna E#in[1.58, 2.51] TeV; #alpha [#circ]; #delta [#circ]",68,-10,10,114,-10,10);
//68 bines en X y 114 en Y reducen la cantidad de bines vacios.

Int_t contador = 0;
//Llenamos el histograma.
while(contador < maxrows){
    infile >> AR >> Dec >> Sig; 
    if(AR<10 && AR>-10){
        if(Dec>-10 && Dec<10){
            H->Fill(AR,Dec,Sig);
        }
    }
    contador ++;
}

gStyle->SetPalette(kRainBow); //Color map estilo arcoiris.
H->SetStats(0); //Sin la caja de datos estadísticos
H->Draw("colz");
auto text = new TLatex(10.2,10.8,"[#sigma]");
text->Draw("same");
cv->cd(1);
cv->SaveAs("MapaLunar.pdf");
}
