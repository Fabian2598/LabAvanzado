#include <vector>
#include "TGraph.h"

//Punto 3 del proyecto.
void P3(){
const long int maxrows = 12*256*256-1; //Número de elementos de cada archivo.

Double_t AR, Dec, Sig; 
const char *Nombres[10] = {"luna_protonlhe/tabla_0.dat", "luna_protonlhe/tabla_1.dat", "luna_protonlhe/tabla_2.dat",
"luna_protonlhe/tabla_3.dat", "luna_protonlhe/tabla_4.dat", "luna_protonlhe/tabla_5.dat",
"luna_protonlhe/tabla_6.dat","luna_protonlhe/tabla_7.dat","luna_protonlhe/tabla_8.dat",
"luna_protonlhe/tabla_9.dat"};

TString file; 
Int_t contador;

Double_t ARmin[10], Decmin[10], Sigmin[10], bines[10];

for(int i=0; i<10; i++ ){
    file = Nombres[i];
    std::ifstream infile(file.Data());
    contador = 0;
    ARmin[i] = 0; Decmin[i] = 0; Sigmin[i] = 0; bines[i] = i;
    while(contador < maxrows){
        infile >> AR >> Dec >> Sig;
        //Iteramos para encontrar el valor mínimo de la signficancia en cada uno de los bines.
        //Guardamos el valor mínimo de la significancia así como sus coordenadas.
        if (i==0){ if(Sig<Sigmin[0]){Sigmin[0]=Sig; ARmin[0]=AR; Decmin[0]=Dec;} }
        if (i==1){ if(Sig<Sigmin[1]){Sigmin[1]=Sig; ARmin[1]=AR; Decmin[1]=Dec;} }
        if (i==2){ if(Sig<Sigmin[2]){Sigmin[2]=Sig; ARmin[2]=AR; Decmin[2]=Dec;} }
        if (i==3){ if(Sig<Sigmin[3]){Sigmin[3]=Sig; ARmin[3]=AR; Decmin[3]=Dec;} }
        if (i==4){ if(Sig<Sigmin[4]){Sigmin[4]=Sig; ARmin[4]=AR; Decmin[4]=Dec;} }
        if (i==5){ if(Sig<Sigmin[5]){Sigmin[5]=Sig; ARmin[5]=AR; Decmin[5]=Dec;} }
        if (i==6){ if(Sig<Sigmin[6]){Sigmin[6]=Sig; ARmin[6]=AR; Decmin[6]=Dec;} }
        if (i==7){ if(Sig<Sigmin[7]){Sigmin[7]=Sig; ARmin[7]=AR; Decmin[7]=Dec;} }
        if (i==8){ if(Sig<Sigmin[8]){Sigmin[8]=Sig; ARmin[8]=AR; Decmin[8]=Dec;} }
        if (i==9){ if(Sig<Sigmin[9]){Sigmin[9]=Sig; ARmin[9]=AR; Decmin[9]=Dec;} }
        contador ++;
    }
}

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
gr->SetTitle("Significancia m#acute{i}nima (protonlhe)");
gr->GetXaxis()->SetTitle("Bin");
gr->GetYaxis()->SetTitle("Significancia [#sigma]");
gr->Draw("ALP");
cs->cd(1);


cs->Update();
cs->GetFrame()->SetFillColor(21);
cs->Modified();
cout<<"El valor mínimo se encuentra en el bin "<<bin<<" y corresponde a una ascención recta de "<<am<<" y a una declinación de " <<dm<<endl; 
cout<<"Corresponde a "<<sm<<" sigmas"<<endl;

cs->SaveAs("Sig_plhe.pdf");
}
