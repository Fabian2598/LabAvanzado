#include <iostream>

//Cambiar el main cuando lo pase a root.
int main() {
	int x;
	std::cout << "Digite un numero entero " << std::endl; //No pongo acentos.
	char DNuevo = 'y';
	while (DNuevo == 'y') {
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
	return 0;
}
