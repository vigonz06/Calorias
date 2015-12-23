#include "ListaAlimentos.h"
#include "GraphInter.h"

void ListaAlimentos::añadir()
{
	Alimento* nuevo = new Alimento;

	GraphInter::get()->display("Que alimento quieres agregar?");
	GraphInter::get()->enter(nuevo->nombre);

	GraphInter::get()->display("Cuantas Kcal tiene?");
	GraphInter::get()->enter(nuevo->calorias);

	GraphInter::get()->display("En que cantidad tiene esas calorias?");
	GraphInter::get()->enter(nuevo->cantidad);

	nuevo->solid = GraphInter::get()->traducir2();


	if (!this->insert(nuevo))
	{
		GraphInter::get()->display("El alimento no pudo insertarse en la base de datos");
		GraphInter::get()->pausa();

		delete nuevo;
	}
}

void ListaAlimentos::editar()
{
	std::string nombre;
	int ini = 0, fin = this->length() - 1, pos = 0;

	GraphInter::get()->display("Que alimento quieres editar?");
	GraphInter::get()->enter(nombre);

	if (this->search(nombre, pos, ini, fin))
	{
		GraphInter::get()->display("Cuantas Kcal tiene?");
		GraphInter::get()->enter(this->list[pos]->calorias);

		GraphInter::get()->display("En que cantidad tiene esas calorias?");
		GraphInter::get()->enter(this->list[pos]->cantidad);

		this->list[pos]->solid = GraphInter::get()->traducir2();
	}
	else
	{
		GraphInter::get()->display("Este alimento no se encuentra en la base de datos");
		GraphInter::get()->pausa();
	}
}

void ListaAlimentos::eliminar()
{
	std::string nombre;
	int ini = 0, fin = this->length() - 1, pos = 0;

	GraphInter::get()->display("Que alimento quieres eliminar?");
	GraphInter::get()->enter(nombre);

	if (!this->destroy(nombre))
	{
		GraphInter::get()->display("Este alimento no se encuentra en la base de datos");
		GraphInter::get()->pausa();
	}
}

void ListaAlimentos::mostrarUno()
{
	std::string nombre;
	int ini = 0, fin = this->length() - 1, pos = 0;

	if (!this->empty())
	{
		GraphInter::get()->display("Que alimento quieres mostrar?");
		GraphInter::get()->enter(nombre);
		GraphInter::get()->clearConsole();

		if (this->search(nombre, pos, ini, fin))
		{
			GraphInter::get()->display("Alimento:");
			GraphInter::get()->mostrar(this->list[pos]);
			GraphInter::get()->pausa();
		}
		else
		{
			GraphInter::get()->display("Este alimento no se encuentra en la lista");
			GraphInter::get()->pausa();
		}
	}
	else
	{
		GraphInter::get()->display("La lista esta vacia");
		GraphInter::get()->pausa();
	}
}

void ListaAlimentos::mostrarTodos()
{
	if (!this->empty())
	{
		GraphInter::get()->display("Alimentos:");

		for (int i = 0; i < this->length(); i++)
		{
			GraphInter::get()->mostrar(this->list[i]);
		}
		GraphInter::get()->pausa();
	}
	else
	{
		GraphInter::get()->display("La lista esta vacia");
		GraphInter::get()->pausa();
	}
}