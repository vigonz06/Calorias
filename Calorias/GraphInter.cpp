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

std::string GraphInter::minus(std::string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] >= 65 && word[i] <= 90)
		{
			word[i] += 32;
		}
	}
	return word;
}

int GraphInter::traducir()
{
	std::string comida;

	do
	{
		display("Que comida acabas de terminar?");
		enter(comida);

		if (minus(comida) == "desayuno")
		{
			return 0;
		}
		else if (minus(comida) == "comida")
		{
			return 1;
		}
		else if (minus(comida) == "merienda")
		{
			return 2;
		}
		else if (minus(comida) == "cena")
		{
			return 3;
		}
		else
		{
			display("Eso no es ninguna comida");

			comida = "none";
		}
	} while (comida == "none");
}

bool GraphInter::traducir2()
{
	std::string medida;

	display("Medida en gramos, o en mililitros?");
	enter(medida);

	do
	{
		if (minus(medida) == "gramos") return true;

		else if (minus(medida) == "mililitros") return false;

		else
		{
			display("Eso no es una medida valida");

			medida = "none";
		}
	} while (medida == "none");
}

std::string GraphInter::traducir(int comida)
{
	switch (comida)
	{
	case 0:
		return "Desayuno: ";
		break;
	case 1:
		return "Comida: ";
		break;
	case 2:
		return "Merienda: ";
		break;
	case 3:
		return "Cena: ";
		break;
	}
}

std::string GraphInter::traducir2(bool solid)
{
	if (!solid) return "ml";

	if (solid) return "g";
}

void GraphInter::mostrar(Persona* persona)
{
	display(persona->nombre + ":");

	for (int i = 0; i < COMIDAS; i++)
	{
		if (!persona->comidas[i].empty())
		{
			display(tab_word(traducir(i)));

			for (int j = 0; j < persona->comidas[i].length(); j++)
			{
				mostrar(persona->comidas[i].operator[](j));
			}
		}
	}
	display("");
	display(tab_word("Kcal consumidas: " + std::to_string(persona->calorias)));
	display(tab_word("Meta diaria de Kcal: " + std::to_string(persona->meta)));

	if (persona->meta < persona->calorias)
	{
		display(tab_word("Meta diaria sobrepasada"));
	}
	else if (persona->meta > persona->calorias)
	{
		display(tab_word("Kcal restantes hasta la meta: " + std::to_string(persona->meta - persona->calorias)));
	}
	else
	{
		display(tab_word("Meta diaria lograda"));
	}
	display("");
}

void GraphInter::mostrar(Comida* comida)
{
	display(tab_word(tab_word(comida->nombre + ": " + std::to_string(comida->cantidad) + " " + traducir2(comida->solid))));
}

void GraphInter::mostrar(Alimento* alimento)
{
	display(tab_word(alimento->nombre + ": " + std::to_string(alimento->calorias) + " Kcal por cada " + std::to_string(alimento->cantidad) + " " + traducir2(alimento->solid)));
}

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

int GraphInter::userMenu()
{
	std::string opciones[6];

	opciones[0] = "Agregar";
	opciones[1] = "Editar";
	opciones[2] = "Resetear";
	opciones[3] = "Eliminar";
	opciones[4] = "Mostrar";
	opciones[5] = "Volver";

	return menu(opciones, 6);
}

int GraphInter::foodMenu()
{
	std::string opciones[5];

	opciones[0] = "Agregar";
	opciones[1] = "Editar";
	opciones[2] = "Eliminar";
	opciones[3] = "Mostrar";
	opciones[4] = "Volver";

	return menu(opciones, 5);
}

int GraphInter::multMenu()
{
	std::string opciones[3];

	opciones[0] = "Uno";
	opciones[1] = "Todos";
	opciones[2] = "Volver";

	return menu(opciones, 3);
}

