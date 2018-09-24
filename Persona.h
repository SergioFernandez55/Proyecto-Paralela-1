#pragma once
class Persona
{
private:
	int estado; // 1 es sano, 2 es enfermo, 3 es inmune y 4 muerto
	int diasEnfermo;

public:
	Persona(int estado);
	~Persona();
	inline int aumentarDias() { return ++diasEnfermo; }
	inline int getEstado() { return estado; }
	inline void setEstado(int e) { estado = e; }
};