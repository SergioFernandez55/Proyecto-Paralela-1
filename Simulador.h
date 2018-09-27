#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <thread>
#include <vector>

class Persona;

class Simulador
{

private:
	int numPersonas;
	float potenciaVirus;
	float probRecuperacion;
	float probMuerte;
	float porcentajeInfectados;
	int tamano;
	int numeroNucleos;
	std::vector< std::vector < std::vector < Persona* > > > personas;

public:
	Simulador(int numPersonas, float potenciaVirus, float probRecuperacion, float probMuerte, float porcentajeInfectados, int tamano);
	~Simulador();
	int ejecutar(int tics);
	void llenarMatriz();
	void modificarEstados();
	void moverPersonas();
};
