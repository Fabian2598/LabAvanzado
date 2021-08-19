#include <iostream>


void ParImpar() {
	int x;
	char DNuevo = 'y';
	while (DNuevo == 'y') {
		std::cout << "Digite un numero entero " << std::endl; //No pongo acentos.
		int fact = 1;
		std::cin >> x;
		if ((x%2) == 0) {
			std::cout << "Su numero es par" << std::endl;
		}
		else {
			std::cout << "Su numero es impar" << std::endl;
		}
		std::cout << "¿Desea probar otro numero? (y/n) " << std::endl;
		std::cin >> DNuevo;
	}
	
}
