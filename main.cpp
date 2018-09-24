#include <iostream>
#include <omp.h> 
#include <string>
#include "Simulador.h"
using namespace std;



int main() {
	int numPersonas;
	float potenciaVirus;
	float probRecuperacion;
	float probMuerte;
	float porcentajeIntectados;
	int tamano;
	int duracion;
	std::vector <std::string> salidas;
	cout << "Ingrese la cantidad de personas (0 a 10.000.000): ";
	cin >> numPersonas;
	cout << endl;
	while (numPersonas <= 0 || numPersonas > 10000000)
	{
		cout << "Numero de personas no válido." << endl << "Ingrese la cantidad de personas (0 a 10.000.000): ";
		cin >> numPersonas;
		cout << endl;
	}
	cout << "Ingrese el porcentaje de la potencia del virus (0 a 99): ";
	cin >> potenciaVirus;
	cout << endl;
	while (potenciaVirus <= 0 || potenciaVirus > 99)
	{
		cout << "Porcentaje de la potencia de virus no válido" << endl << "Ingrese el porcentaje de la potencia del virus (0 a 99): ";
		cin >> potenciaVirus;
		cout << endl;
	}
	cout << "Ingrese el porcentaje de la probabilidad de recuperacion (0 a 99): ";
	cin >> probRecuperacion;
	cout << endl;
	while (probRecuperacion <= 0 || probRecuperacion > 99)
	{
		cout << "Porcentaje de la de la probabilidad de recuperacion no válido" << endl << "Ingrese el porcentaje de la probabilidad de recuperacion (0 a 99): ";
		cin >> probRecuperacion;
		cout << endl;
	}
	cout << "Ingrese el porcentaje de la probabilidad de muerte (0 a 99): ";
	cin >> probMuerte;
	cout << endl;
	while (probMuerte <= 0 || probMuerte > 99)
	{
		cout << "Porcentaje de la de la probabilidad de muerte no válido" << endl << "Ingrese el porcentaje de la probabilidad de muerte (0 a 99): ";
		cin >> probMuerte;
		cout << endl;
	}
	cout << "Ingrese el porcentaje de personas infectadas inicialmente (0 a 10): ";
	cin >> porcentajeIntectados;
	cout << endl;
	while (porcentajeIntectados <= 0 || porcentajeIntectados > 99)
	{
		cout << "Porcentaje de personas infectadas inicialmente no válido" << endl << "Ingrese el porcentaje de personas infectadas inicialmente (0 a 99): ";
		cin >> porcentajeIntectados;
		cout << endl;
	}
	cout << "Ingrese el tamaño del mundo (100, 500 o 1000): ";
	cin >> tamano;
	cout << endl;
	while (tamano != 100 && tamano != 500 && tamano != 1000)
	{
		cout << "Tamaño del mundo no válido" << endl << "Ingrese el tamaño del mundo (100, 500 o 1000): ";
		cin >> tamano;
		cout << endl;
	}
	cout << "Ingrese la cantidad de días que va a durar la simulacion" << endl;
	cin >> duracion;
	cout << endl;
	while (duracion <= 0)
	{
		cout << "Porcentaje de personas infectadas inicialmente no válido" << endl << "Ingrese el porcentaje de personas infectadas inicialmente (0 a 99): ";
		cin >> duracion;
		cout << endl;
	}

	Simulador sim(numPersonas, potenciaVirus, probRecuperacion, probMuerte, porcentajeIntectados, tamano);
	sim.ejecutar(duracion);
	for (int salida = 0; salida < salidas.size(); ++salida) {

	}
}