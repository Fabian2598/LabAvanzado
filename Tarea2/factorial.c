#include <iostream>


void factorial(){
int x;
char DNuevo = 'y';
while (DNuevo == 'y') {
	std::cout << "Digite un numero entero " << std::endl; //No pongo acentos.
	long long int fact = 1;
	std::cin >> x;
	if (x != 0) {
		for (int i = 1; i <= x; i++) {
			fact = i * fact; //Calculamos el factorial con un ciclo for.
		}
	}
	std::cout << "El factorial de " << x << " es " << fact << std::endl;
	std::cout << "¿Desea calcular otro factorial? (y/n) " << std::endl;
	std::cin >> DNuevo;
	}
}
