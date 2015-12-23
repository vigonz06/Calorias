#include "Persona.h"

void Persona::save(std::ofstream &file)
{
	file << this->nombre << std::endl
		<< this->calorias << std::endl
		<< this->meta << std::endl;
}

bool Persona::load(std::ifstream &file)
{
	file >> this->nombre;

	if (!file.fail())
	{
		file >> this->calorias;

		if (!file.fail())
		{
			file >> this->meta;

			if (!file.fail()) return true;

			else return false;
		}
		else return false;
	}
	else return false;
}