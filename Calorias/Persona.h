#ifndef PERSONA
#define PERSONA

#include <string>
#include <fstream>
#include "ListaComida.h"
#include "GlobalConstants.h"

struct Persona
{
	std::string nombre;
	ListaComida comidas[COMIDAS];
	int calorias;
	int meta;

	void save(std::ofstream &file);
	bool load(std::ifstream &file);
};

#endif