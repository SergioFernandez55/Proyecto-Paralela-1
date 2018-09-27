#include "Simulador.h"
#include "Persona.h"


Simulador::Simulador(int numPersonas, float potenciaVirus, float probRecuperacion, float probMuerte, float porcentajeInfectados, int tamano)
{
	this->numPersonas = numPersonas;
	this->potenciaVirus = potenciaVirus;
	this->probRecuperacion = probRecuperacion;
	this->probMuerte = probMuerte;
	this->porcentajeInfectados = porcentajeInfectados;
	this->tamano = tamano;
	this->personas.resize(numPersonas);
	this->numeroNucleos = std::thread::hardware_concurrency();
	this->porcentajeEnfermas = porcentajeInfectados;
	this->porcentajeSanas = 100 - porcentajeInfectados;
	this->porcentajeInmunes = 0;
	this->porcentajeMuertas = 0;
	personas.resize(tamano);
	for (int columna = 0; columna < tamano; ++columna)
		personas[columna].resize(tamano);
}


Simulador::~Simulador()
{
	personas.clear();
}

int Simulador::ejecutar(int tics)
{
	std::cout << "Este programa utilizara " << numeroNucleos << " nucleos." << std::endl;
	this->llenarMatriz();
	for (int tic = 0; tic < tics; ++tic)
	{
		this->modificarEstados();
		this->moverPersonas();
		this->imprimir();
	}
	return 0;
}

void Simulador::llenarMatriz()
{
	int personasInfectadas = numPersonas * (porcentajeInfectados / 100);
	int personasSanas = numPersonas - personasInfectadas;
	srand(4 ^ time(NULL)+5);
#if 1
	std::cout << "Llenando con enfermos" << std::endl;
#endif
	for (int persona = 0; persona < personasInfectadas; persona++)
	{
		Persona* nuevo = new Persona(2);
		nuevo->aumentarDias();
		int x = rand() % this->tamano;
		int y = rand() % this->tamano;
		personas[x][y].push_back(nuevo);
#if 1
		std::cout << "Persona enferma agregada en " << x << ',' << y << std::endl;
#endif
	}
#pragma omp parallel num_threads(numeroNucleos*4)
	srand(4 ^ time(NULL));
#pragma omp for
	for (int persona = 0; persona < personasSanas; persona++)
	{
		Persona* nuevo = new Persona(1);
		int x = rand() % this->tamano;
		int y = rand() % this->tamano;
#pragma omp critical
		personas[x][y].push_back(nuevo);
#if 1
#pragma omp critical
		std::cout << "Persona sana agregada en " << x << ',' << y << std::endl;
#endif
	}
}

void Simulador::moverPersonas()
{

}

void Simulador::imprimir()
{

}

void Simulador::modificarEstados(int tic)
{
	omp_set_nested(1);
	std::vector<int> listaEstados;
	int cantEnfermos = 0;
	int cantSanos = 0;
	int cantInmunes = 0;
	int cantMuertos = 0;
#pragma omp parallel for num_threads(numeroNucleos*2)
	for (int fila = 0; fila < tamano; ++fila)
#pragma omp parallel for num_threads(2)
		for (int columna = 0; columna < tamano; ++columna)
		{
			if (!personas[fila][columna].empty())
			{
				listaEstados.resize(personas[fila][columna].size());
				for (int i = 0; i < personas[fila][columna].size(); ++i) 
				{
					switch (personas[fila][columna][i]->getEstado()) {
					case 1:
						++cantSanos;
						break;
					case 2:
						++cantEnfermos;
						break;
					case 3:
						++cantInmunes;
						break;
					case 4:
						++cantMuertos;
						break;
					}
				}
				for (int i = 0; i < listaEstados.size(); ++i)
				{
					if (personas[fila][columna][i]->getEstado() == 1) {
#if 1
#pragma omp critical
						std::cout << "Persona en " << fila << ',' << columna << " está sano" << std::endl;
#endif
						for (int enfermo = 0; enfermo < cantEnfermos; ++enfermo)
						{
							int enfermarse = rand() % 100;
							if (enfermarse < potenciaVirus)
							{
								listaEstados[i] = 2;
							}
						}
					}
					if (personas[fila][columna][i]->getEstado() == 2) {
#if 1
#pragma omp critical
						std::cout << "Persona en " << fila << ',' << columna << " está enfermo" << std::endl;
#endif
						int sanarse = rand() % 100;
						if (sanarse < probRecuperacion)
						{
							listaEstados[i] = 3;
						}
					}
#if 1
					if (personas[fila][columna][i]->getEstado() == 3) 
#pragma omp critical
						std::cout << "Persona en " << fila << ',' << columna << " está muerto" << std::endl;
					if (personas[fila][columna][i]->getEstado() == 4)
#pragma omp critical
						std::cout << "Persona en " << fila << ',' << columna << " está inmune" << std::endl;
#endif
				}
				/*for (int i = 0; i < personas[fila][columna].size(); ++i)
				{
					personas[fila][columna][i]->setEstado(listaEstados[i]);
				}*/
			}
		}
	std::cout << "Tic " << tic << ":" << std::endl;
	
}
