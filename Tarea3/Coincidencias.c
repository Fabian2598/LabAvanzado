#include <iostream>
#include <vector> 
#include <cmath>


/* Usaremos el detector P11. De acuerdo al xml, los canales de sus cuatro PMT son
681, 682, 683 y 684.
<tank id="171">
<name> P11 </name>
<type> 1 </type>
<position>
<x unit="cm"> 2278.93 </x>
<y unit="cm"> 25326.60 </y>
<z unit="cm"> -0.78 </z>
</position>
<channels>
<channel id="681">
<name> P11A </name>
<number> 1 </number>
<type> 1 </type>
<position>
<x unit="cm"> -132.17 </x>
<y unit="cm"> 128.90 </y>
<z unit="cm"> 29.45 </z>
</position>
</channel>
<channel id="682">
<name> P11B </name>
<number> 2 </number>
<type> 1 </type>
<position>
<x unit="cm"> 178.47 </x>
<y unit="cm"> 49.11 </y>
<z unit="cm"> 31.42 </z>
</position>
</channel>
<channel id="683">
<name> P11C </name>
<number> 3 </number>
<type> 2 </type>
<position>
<x unit="cm"> 0.00 </x>
<y unit="cm"> 0.00 </y>
<z unit="cm"> 33.87 </z>
</position>
</channel>
<channel id="684">
<name> P11D </name>
<number> 4 </number>
<type> 1 </type>
<position>
<x unit="cm"> -46.68 </x>
<y unit="cm"> -179.26 </y>
<z unit="cm"> 31.35 </z>
</position>
</channel>
</channels>
</tank>

*/
//Implementaremos tres funciones que nos servirán más adelante.
//Usaremos esta función que acomoda los elementos de un conjunto de menor a mayor. La función fue realizada
//en la primera tarea.
std::vector<double> Sort ( std::vector<double> x){
//Ordenando de menor a mayor
	for (int i = 1; i < x.size(); i++) {
		int j = i - 1; 
		float ini;
		while (x[j] > x[j+1]) {
			ini = x[j + 1];
			x[j + 1] = x[j];
			x[j] = ini;
			if(j!=0){
				j -= 1;
			}
		}
	}
    return x;

} 

//Como tendremos varias coincidencias, debemos asignar un promedio al tiempo entre ellas. Con este
//resultado, podemos calcular la frecuencia como 1/t
double MeanTime(std::vector<double> x){
    //Cálculo del tiempo promedio entre cada coincidencia. x es
    //el arreglo compuesto por los tiempos a los que hay coincidencias.
    double prom=0;
    int N = x.size();
    for(int i=0; i<N-1; i++){
        prom += abs(x[i+1]-x[i]);
    }
    return prom/(N-1);
}

//Error estándar asociado el tiempo promedio entre cada medición.
double std_error(std::vector<double> x) {
    double var = 0; //Varianza
    int N = x.size();
    double prom = MeanTime(x);
    for(int i=0; i<N-1; i++){
        var += (abs(x[i]- x[i+1])-prom) * (abs(x[i]- x[i+1])-prom) ;
    }
    var = var/(N-1) ;
    //El error estándar es igual a la raíz de la varianza entre el número de mediciones. Como tenemos N coincidencias,
    // hay N-1 tiempos entre cada coincidencia.
    return sqrt(var/ (N-1) );
}

void Coincidencias(){

 //Importamos los datos
TFile *file = TFile::Open("raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");

Int_t entradas = arbol->GetEntries();
Double_t CTime;
UInt_t ChannelInfo;
std::vector<Double_t>  CTimes, TdCoin;
//En CTimes guardaremos los tiempos a los que miden los detectores. 
//En TdCoin vamos a guardar aquellos tiempos a los que hay coincidencias.

arbol->SetBranchAddress("Channel", &ChannelInfo);
arbol->SetBranchAddress("CalibratedTime", &CTime);

//Guardamos los tiempos a los que miden los PMT, los cuatro en un mismo arreglo, sin importar el detector.
for(Int_t i=0;i<entradas;i++){
    arbol->GetEntry(i);
    if (ChannelInfo == 681){
        CTimes.push_back(CTime);
    }
    else if (ChannelInfo == 682){
        CTimes.push_back(CTime);
    }
     else if (ChannelInfo == 683){
        CTimes.push_back(CTime);
    }
    else if (ChannelInfo == 684){
        CTimes.push_back(CTime);
    }

}
CTimes = Sort(CTimes); //Acomodamos los tiempos de menor a mayor.

/*Contamos una coincidencia cuando dos PMT detectan en una ventana de 20 nS. Para el algoritmo asumiremos que un mismo PMT no mide dos veces
en una ventana de 20 ns, lo cual se puede corroborar que es cierto revisando los tiempos de coincidencia de cada PMT del detector. El proceso 
que se realiza es el siguiente: Empezamos con el primer elemento de CTimes, arreglo que está ordenado de menor a mayor. Revisamos si abs(CTimes[0]-CTimes[1])<20 ns,
de no ser así, el algoritmo se pasa a revisar la diferencia abs(CTimes[1]-CTimes[2]). Ahora bien, si efectivamente la diferencia es menor a 20 ns, tenemos una 
coincidencia entre dos detectores y además, podría ocurrir alguno de los dos casos:

1) Que la diferencia abs(CTimes[0]-CTimes[2])<20 ns. En esta situación tenemos un tercer detector que también entra en la ventana de los 20 ns, para evitar 
que el algoritmo detecte una coincidencia al momento de verificar que abs(CTimes[1]-CTimes[2])<20 ns (lo cual va a ocurrir ya que todo está en orden ascendente),
nos debemos de saltar el elemento CTimes[1] en el procedimiento. Pueden nuevamente ocurrir dos casos:
    1.1) Que la diferencia abs(CTimes[0]-CTimes[3])<20 ns. En este caso los cuatro PMT detectan una coincidencia. Para evitar que la coincidencia se tome en cuenta
    más de una vez, nos pasaremos al elemento CTimes[4] y le aplicaremos los pasos anteriores.  Ya no será necesario revisar si abs(CTimes[0]-CTimes[4])<20,
    puesto que a lo más tenemos cuatro detectores y asumimos que si todos estos coinciden, la siguiente medición se hará en una ventana mayor a 20 ns. 
    1.2) Que la diferencia abs(CTimes[0]-CTimes[3])>20 ns. En este caso no hay detección en coincidencia con el cuarto detector en la ventana de los 20 ns y nos pasamos
    a repetir los pasos anteriores a CTimes[3].
2)Que la diferencia abs(CTimes[0]-CTimes[2])>20 ns. En este caso nos pasamos a aplicar los pasos anteriores al CTimes[2].

Lo que sigue es ir aplicando los pasos anteriores de manera iterativa hasta terminar con el conjunto CTimes, formado por todos los tiempos a los que miden los detectores.

*/

//Implementación del algoritmo.
int j = 0;
while (j<CTimes.size()){
    if ( abs(CTimes[j]-CTimes[j+1])<20 && (j+2)<CTimes.size()){

        if ( abs( CTimes[j]-CTimes[j+2] )<20 && (j+3)<CTimes.size()){

            if (  abs(CTimes[j] - CTimes[j+3]) <20 && (j+4)<CTimes.size()){
                TdCoin.push_back(CTimes[j]);
                j+=4;

            }
            else{
                TdCoin.push_back(CTimes[j]);
                j+=3;
            }

        }
        else{
            TdCoin.push_back(CTimes[j]);
            j+=2; 
        }
    }

    else{
        j += 1;
    }
}


//Calculemos la frecuencia promedio entre coincidencias
double TMedio = MeanTime(TdCoin)*1e-9, dMeanTime = std_error(TdCoin)*1e-9; //   En segundos 
std::cout << "El tiempo promedio entre coincidencias del detector P11 es: " << TMedio << " +- " << dMeanTime  << " seg" << std::endl;
std::cout << "La frecuencia promedio es: " << 1/TMedio << " +- " << dMeanTime/(TMedio*TMedio) << " Hz" << std::endl;
//Estamos usando el hecho de que si tenemos una medición x = x0 +- dx, la incertidumbre de 1/x es dx/x0^2.

//Al ejecutar en la terminal la frecuencia da 20,918 +- 294.657 Hz.


//Se puede descomentar el siguiente código para corroborar que el algoritmo funciona de manera adecuada.

/* 
std::cout << "Primeras 100 entradas de CTimes" << std::endl;
for(int i=0; i<100; i++){
    std::cout << CTimes[i] << std::endl;
}


std::cout << "" << std::endl;


std::cout << "Primeros 20 tiempos a los que hay coincidencias" << std::endl;
for(int i=0; i<20;i++){
    std::cout << TdCoin[i] << std::endl;
}
*/


}
