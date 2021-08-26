#include <iostream>
#include <vector> 

/*
Datos del F14
<tank id="18">
<name> F14 </name>
<type> 1 </type>
<position>
<x unit="cm"> 10747.68 </x>
<y unit="cm"> 26113.95 </y>
<z unit="cm"> 0.56 </z>
</position>
<channels>
<channel id="69">
<name> F14A </name>
<number> 1 </number>
<type> 1 </type>
<position>
<x unit="cm"> -46.50 </x>
<y unit="cm"> -176.93 </y>
<z unit="cm"> 30.34 </z>
</position>
</channel>

Datos del H13C
<tank id="46">
<name> H13 </name>
<type> 1 </type>
<position>
<x unit="cm"> 9134.78 </x>
<y unit="cm"> 25665.44 </y>
<z unit="cm"> 0.70 </z>
</position>
<channels>
<channel id="183">
<name> H13C </name>
<number> 3 </number>
<type> 2 </type>
<position>
<x unit="cm"> 0.00 </x>
<y unit="cm"> 0.00 </y>
<z unit="cm"> 34.37 </z>
</position>
</channel>

Canales: channel id 69-->F14A  id del tanque =18 Tanque 18
         183-->H13C, id del tanque = 46
*/

void Analisis(){

TFile *file = TFile::Open("raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");

Int_t entradas = arbol->GetEntries();
Double_t Charge;
UInt_t ChannelInfo, Flag;
std::vector<Double_t> CargaF14A, CargaH13C, CargaF14A_CS, CargaH13C_CS;
//CargaF14A--> Carga sin selección de calidad
//CargaF14A_CS --> Carga con selección de calidad

arbol->SetBranchAddress("Channel", &ChannelInfo);
arbol->SetBranchAddress("CalibratedCharge", &Charge);
arbol->SetBranchAddress("FLAGS", &Flag);
for(Int_t i=0;i<entradas;i++){
    arbol->GetEntry(i);
    //Guardamos las cargas en los arreglos
    if (ChannelInfo == 69){
        CargaF14A.push_back(Charge);
        if (Flag == 0){
            CargaF14A_CS.push_back(Charge);
        }
    }
    else if (ChannelInfo == 183){
        CargaH13C.push_back(Charge);
        if (Flag == 0){
            CargaH13C_CS.push_back(Charge);
        }
    }
}


int Bins = 500; //Se puede cambiar el número de bins.

//Esto nos ayuda a encontrar el elemento máximo de un arreglo. Lo colocamos por si se desea graficar el histograma
//hasta el rango máximo posible de valores.
double maxh1 = *std::max_element(CargaF14A.begin(), CargaF14A.end());
double maxh2 = *std::max_element(CargaF14A_CS.begin(), CargaF14A_CS.end());
double maxh3 = *std::max_element(CargaH13C.begin(), CargaH13C.end());
double maxh4 = *std::max_element(CargaH13C_CS.begin(), CargaH13C_CS.end());

//Definimos a los histogramas
TH1D *h1 = new TH1D("F14A_SS","Distribucion de carga, F14A sin seleccion; Carga; Cuentas",Bins,0,10);
TH1D *h2 = new TH1D("F14A_CS","Distribucion de carga, F14A con seleccion; Carga; Cuentas",Bins,0,10);
TH1D *h3 = new TH1D("H13C_SS","Distribucion de carga, H13C sin seleccion; Carga; Cuentas",Bins,0,10);
TH1D *h4 = new TH1D("H13_CS","Distribucion de carga, H13C con seleccion; Carga; Cuentas",Bins,0,10);

//Debemos guardar cada elemento de los arreglos en los objetos h para graficar el histograma.
for (int i=0; i<CargaF14A.size(); i++){
    h1->Fill(CargaF14A[i]);
}

for (int i=0; i<CargaF14A_CS.size(); i++){
    h2->Fill(CargaF14A_CS[i]);
}

for (int i=0; i<CargaH13C.size(); i++){
    h3->Fill(CargaH13C[i]);
}

for (int i=0; i<CargaH13C_CS.size(); i++){
    h4->Fill(CargaH13C_CS[i]);
}


TCanvas *cs = new TCanvas("cs","canvas");

//cs->SetLogx(); //Por si se desea poner escala logarítmica
h1->Draw();
cs->SaveAs("F14A_SS.png"); //Guardamos los histogramos.
h2->Draw();
cs->SaveAs("F14A_CS.png");
h3->Draw();
cs->SaveAs("H13C_SS.png");
h4->Draw();

cs->SaveAs("H13C_CS.png");


}

