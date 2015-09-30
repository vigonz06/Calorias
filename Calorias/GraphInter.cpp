#include "GraphInter.h"
#include <iostream>
#include "utilsWin.h"
#include <sstream>
#include <iomanip>
#include "GlobalConstants.h"

GraphInter* GraphInter::inter = nullptr;

GraphInter* GraphInter::get()
{
	return inter;
}

void GraphInter::load()
{
	if (inter == nullptr)
	{
		inter = new GraphInter;
	}
}

void GraphInter::close()
{
	if (inter != nullptr)
	{
		delete inter;
	}
}

void GraphInter::display(std::string word)
{
	std::cout << word << std::endl;
}

void GraphInter::display(int numero)
{
	std::cout << numero << std::endl;
}

void GraphInter::enter(std::string &word)
{
	std::cin.sync();
	std::cin >> word;
}

void GraphInter::enter(int &numero)
{
	std::cin.sync();
	std::cin >> numero;
}

int GraphInter::digitoEntre(int a, int b)
{
	int digito = -1;

	do
	{
		enter(digito);

		if (std::cin.fail())
		{
			std::cout << "Error, introduce un digito" << std::endl;
			std::cin.clear();
		}

		else if (digito < a || digito > b)
		{
			std::cout << "Error, introduce un digito entre " << a << " y " << b << std::endl;
			digito = -1;
		}

	} while (digito == -1);

	return digito;
}

/*void GraphInter::mostrar(Persona* persona)
{
	display(persona->nombre);

	for (int j = 0; j < persona->comida.length(); j++)
	{
		mostrar(persona->comida.operator[](j));
	}
}

void GraphInter::mostrar(Comida* comida)
{
	display(comida->nombre + ": " + std::to_string(comida->cantidad) + " g -> " + std::to_string(comida->calorias_peso));
}*/

void GraphInter::pausa()
{
	std::cin.sync();
	std::cin.get();
}

int GraphInter::update(int key, int elem, int max_elems)
{
	if (key == UP) elem--;
	else if (key == DOWN) elem++;

	if (elem < 0) elem = max_elems - 1;
	else if (elem >= max_elems) elem = 0;

	if (key == ESCAPE) elem = max_elems - 1;
	return elem;
}

int GraphInter::menu(std::string elems[], int max_elems)
{
	int key = UP, elem = 0;

	do
	{
		display("Choose your desired option: ");

		for (int i = 0; i < max_elems; i++)
		{
			tab_word(elems[i], i, elem);
		}

		key = getKey();
		elem = update(key, elem, max_elems);

		clearConsole();

	} while (key != ENTER && key != ESCAPE);

	return elem;
}

void GraphInter::tab_word(std::string word, int pos, int cont)
{
	if (pos == cont)
	{
		word = "->" + word;
	}
	else
	{
		word = tab_word(word);
	}
	display(word);
}

//It prints the word you choose on console,
//after two empty spaces
std::string GraphInter::tab_word(std::string word)
{
	std::ostringstream tab;

	tab << std::setw(word.size() + 2) << word;

	return tab.str();
}

int GraphInter::mainMenu()
{
	std::string opciones[3];

	opciones[0] = "Usuarios";
	opciones[1] = "Alimentos";
	opciones[2] = "Salir";

	return menu(opciones, 3);
}

int GraphInter::secondaryMenu()
{
	std::string opciones[4];

	opciones[0] = "Agregar";
	opciones[1] = "Editar";
	opciones[2] = "Eliminar";
	opciones[3] = "Salir";

	return menu(opciones, 4);
}

