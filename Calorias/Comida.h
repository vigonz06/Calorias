#ifndef COMIDA
#define COMIDA

#include <string>
#include <fstream>

struct Alimento
{
	std::string nombre;
	int calorias;
	int cantidad;
	bool solid;

	void save(std::ofstream &file)
	{
		file << this->nombre << " "
			<< this->calorias << " " 
			<< this->cantidad << " "
			<< this->solid << std::endl;
	}

	bool load(std::ifstream &file)
	{
		file >> this->nombre;

		if (!file.fail())
		{
			file >> this->calorias;

			if (!file.fail())
			{
				file >> this->cantidad;

				if (!file.fail())
				{
					file >> this->solid;

					if (!file.fail()) return true;

					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
};

struct Comida
{
	std::string nombre;
	int cantidad;
	bool solid;

	void save(std::ofstream &file)
	{
		file << this->nombre << " "
			<< this->cantidad << " "
			<< this->solid << std::endl;
	}

	bool load(std::ifstream &file)
	{
		file >> this->nombre;

		if (!file.fail())
		{
			file >> this->cantidad;

			if (!file.fail())
			{
				file >> this->solid;

				if (!file.fail()) return true;

				else return false;
			}
			else return false;
		}
		else return false;
	}
};


#endif