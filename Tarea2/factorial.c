#include <iostream>

//Cambiar el main cuando lo pase a root.
int main(){
int x;
std::cout << "Digite un numero entero " << std::endl; //No pongo acentos.
char DNuevo = 'y';
while (DNuevo == 'y') {
	long long int fact = 1;
	std::cin >> x;
	if (x != 0) {
		for (int i = 1; i <= x; i++) {
			fact = i * fact; //Calculamos el factorial con un ciclo for.
		}
	}
	std::cout << "El factorial de " << x << " es " << fact << std::endl;
	std::cout << "¡Desea calcular otro factorial? (y/n) " << std::endl;
	std::cin >> DNuevo;
	}
return 0;
}
