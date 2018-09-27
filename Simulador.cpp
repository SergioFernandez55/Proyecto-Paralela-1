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
	}
	return 0;
}

void Simulador::llenarMatriz()
{
	int personasInfectadas = numPersonas * (porcentajeInfectados / 100);
	int personasSanas = numPersonas - personasInfectadas;
	srand(omp_get_thread_num() * 4 ^ time(NULL));
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
	}

#pragma omp parallel for num_threads(numeroNucleos*4)
	for (int persona = 0; persona < personasSanas; persona++)
	{
		Persona* nuevo = new Persona(1);
		int x = rand() % this->tamano;
		int y = rand() % this->tamano;
#pragma omp critical
		personas[x][y].push_back(nuevo);
	}
}

void Simulador::moverPersonas()
{

}

void Simulador::modificarEstados()
{
	omp_set_nested(1);
	std::vector<int> listaEstados;
	int cantEnfermos = 0;
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
					if (personas[fila][columna][i]->getEstado() == 2) {
						cantEnfermos++;
					}
				}
				for (int i = 0; i < personas[fila][columna].size(); ++i)
				{
					if (personas[fila][columna][i]->getEstado() == 1) {
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
						int sanarse = rand() % 100;
						if (sanarse < probRecuperacion)
						{
							listaEstados[i] = 3;
						}
					}
				}
				for (int i = 0; i < personas[fila][columna].size(); ++i)
				{
					personas[fila][columna][i]->setEstado(listaEstados[i]);
				}
			}
		}
}
