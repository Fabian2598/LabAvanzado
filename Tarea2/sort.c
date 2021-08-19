#include <iostream>
#include <vector> 

/*Usaremos un algoritmo que se conoce como insertion sort. Supongamos un conjunto de n números.
Para ordenar de menor a mayor la idea es repetir los siguientes pasos para todos los elementos que se encuentren
entre la segunda y última posición de nuestro conjunto:
-Empezamos en la posición i=1 (C++ indexa desde 0). Revisamos si el elemento que está en i=0 es mayor que el elemento 
en la posición i=1. De ser así, intercambiamos sus valores, de lo contrario no hacemos nada.
-Nos pasamos a la posición i=2. Verificamos si el elemento que está en la posición i=1 es mayor que el de
la posición i=2 y en caso de ser así, intercambiamos los elementos. Si esto no ocurre, comparamos si 
el elemento en la posición i=0 es mayor que el elemento en la posición i=2. Si esto sucede, intercambiamos
el elemento de la posición i=0 con el de la posición i=2 y además recorremos el elemento de la posición 
i=1 a la posición i=2. Si el elemento en la posición i=2 es mayoe que los elementos en i=0 y i=1, no hacemos nada.
-Repetimos el mismo procedimiento hasta llegar a i=n.

Para ordenar de mayor a menor seguimos los mismos pasos, pero ahora hacemos las comparaciones al revés, es decir,
donde haya > ponemos <. 

*/

//CAMBIAR EL MAIN CUANDO LO PASE A ROOT
int main() {
	std::vector<float> elementos{  1, 145, 75, 5 ,21, 71, 34, 55, 23, 20, 100, 33};

	std::cout << "El conjunto inicial es: " << std::endl;
	for (int i = 0; i < elementos.size(); i++) {
		std::cout << elementos[i] << ", ";
	}
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	//Ordenando de menor a mayor
	for (int i = 1; i < elementos.size(); i++) {
		int j = i - 1; 
		float ini;
		while (elementos[j] > elementos[j+1]) {
			ini = elementos[j + 1];
			elementos[j + 1] = elementos[j];
			elementos[j] = ini;
			if(j!=0){
				j -= 1;
			}
		}
	}

	//Imprimimos
	std::cout << "El conjunto ordenado de menor a mayor es: " << std::endl;
	for (int i = 0; i < elementos.size(); i++) {
		std::cout << elementos[i] << ", ";
	}
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	//Ordenando de mayor a menor
	elementos = { 1, 145, 75, 5, 21, 71, 34, 55, 23, 20, 100, 33 };
	for (int i = 1; i < elementos.size(); i++) {
		int j = i - 1;
		float ini, fin;
		while (elementos[j] < elementos[j + 1]) {
			ini = elementos[j + 1];
			elementos[j + 1] = elementos[j];
			elementos[j] = ini;
			if (j != 0) {
				j -= 1;
			}
		}
	}

	//Imprimimos
	std::cout << "El conjunto ordenado de mayor a menor es: " << std::endl;
	for (int i = 0; i < elementos.size(); i++) {
		std::cout << elementos[i] << ", ";
	}


	return 0;
}