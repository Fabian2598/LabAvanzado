#include <vector>
#include "TGraph.h"
void t5()
{
//Cargamos los archivos//////////////////////////////////////////////////////
TString file1="luna_protonlhe/bin1/tabla_1.dat";
const int maxrows = 786431; 
//Definimos los vectores/////////////////////////////////////////////////////
std::vector<double> Ascencion1(maxrows,0), Declinacion1(maxrows,0), Significancia1(maxrows,0);
//Definimos los histogramas y las variables////////////////////////////////////
double sm=0,am=0,dm=0, bin=11;
std::vector<double> sigmin(10,0), amin(10,0), dmin(10,0), a(10,0);
auto *H = new TH2F("","Mapa de la luna (E=1.58-2.51TeV); #alpha [#circ] ; #delta [#circ]",68,-10,10,113,-10,10);
//68 y 113
//70,140
H->SetStats(0);
//Hacemos el llenado de los vectores con la información del archivo////////////
Int_t contador = 0;
std::ifstream infile1(file1.Data());
while(contador < maxrows){infile1 >> Ascencion1[contador]>> Declinacion1[contador] >> Significancia1[contador]; contador ++;}
//Llenamos los histogramas//////////////////////////////////////////////////////
for(int i=0;i<maxrows;i++)
{
 if(Ascencion1[i]<10 && Ascencion1[i]>-10)
 {
  if(Declinacion1[i]>-10 && Declinacion1[i]<10)
  {
   bin=Significancia1[i];
   H->Fill(Ascencion1[i],Declinacion1[i],bin);
  }
 }
}

//Los imprimimos y guardamos////////////////////////////////////////////////////
TCanvas *cs = new
TCanvas("cs","canvas");
//gStyle->SetPalette("kRainBow");
H->Draw("colz");

}
