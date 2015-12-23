#include "ListaAlimentos.h"
#include "ListaPersonas.h"
#include "GraphInter.h"

void ListaPersonas::añadir()
{
	Persona* nuevo = new Persona;

	GraphInter::get()->display("A quien quieres aladir?");
	GraphInter::get()->enter(nuevo->nombre);

	GraphInter::get()->display("Cuantas Kcal quieres consumir hoy?");
	GraphInter::get()->enter(nuevo->meta);

	nuevo->calorias = 0;

	if (!this->insert(nuevo))
	{
		GraphInter::get()->display("El usuario no pudo insertarse en la base de datos");
		GraphInter::get()->pausa();

		delete nuevo;
	}
}

void ListaPersonas::editar(ListaAlimentos* lista)
{
	Comida* nueva;
	std::string nombre, alimento;
	int ini, fin, pos, pri, ult, loc;
	int meta, comida, cantidad, calalim, canalim;

	GraphInter::get()->display("A quien quieres editar?");
	GraphInter::get()->enter(nombre);
	
	ini = 0, fin = this->length() - 1, pos = 0;

	if (this->search(nombre, pos, ini, fin))
	{
		GraphInter::get()->display("Cuantas Kcal queres consumir? (0 para conservar tu objetivo actual)");
		GraphInter::get()->enter(meta);

		if (meta != 0)
		{
			this->list[pos]->meta = meta;
		}

		comida = GraphInter::get()->traducir();

		GraphInter::get()->display("Que alimento quieres agregar? ('nada' para terminar)");
		GraphInter::get()->enter(alimento);

		while (alimento != "nada")
		{
			pri = 0, ult = lista->length() - 1, loc = 0;

			if (lista->search(alimento, loc, pri, ult))
			{
				nueva = new Comida;
				calalim = lista->operator[](loc)->calorias;
				canalim = lista->operator[](loc)->cantidad;

				GraphInter::get()->display("Que cantidad has ingerido?");
				GraphInter::get()->enter(cantidad);

				this->list[pos]->calorias += (calalim * cantidad) / canalim;

				nueva->nombre = alimento;
				nueva->cantidad = cantidad;
				nueva->solid = lista->operator[](loc)->solid;
				this->list[pos]->comidas[comida].insert(nueva);

				if (this->list[pos]->calorias > this->list[pos]->meta)
				{
					GraphInter::get()->display("Cuidado, has sobrepasado tu meta diaria de kcal!");
					GraphInter::get()->pausa();
				}
				if (this->list[pos]->calorias == this->list[pos]->meta)
				{
					GraphInter::get()->display("Atencion, has alcanzado tu meta diaria de kcal!");
					GraphInter::get()->pausa();
				}
			}
			else
			{
				GraphInter::get()->display("Este alimento no se encuentra en la base de datos");
				GraphInter::get()->pausa();
			}

			GraphInter::get()->display("Que alimento quieres agregar? ('nada' para terminar)");
			GraphInter::get()->enter(alimento);
		}
	}
	else
	{
		GraphInter::get()->display("Este usuario no se encuentra en la base de datos");
		GraphInter::get()->pausa();
	}
}

void ListaPersonas::eliminar()
{
	std::string nombre;

	GraphInter::get()->display("A quien quieres eliminar?");
	GraphInter::get()->enter(nombre);

	if (!this->destroy(nombre))
	{
		GraphInter::get()->display("Este usuario no se encuentra en la base de datos");
		GraphInter::get()->pausa();
	}
}

void ListaPersonas::resetear(std::string nombre)
{
	int ini = 0, fin = this->length() - 1, pos = 0;

	if (this->search(nombre, pos, ini, fin))
	{
		this->list[pos]->calorias = 0;

		for (int i = 0; i < COMIDAS; i++)
		{
			for (int j = 0; j < this->list[pos]->comidas[i].length(); j++)
			{
				this->list[pos]->comidas[i].destroy(this->list[pos]->comidas[i].operator[](j)->nombre);
			}
		}
	}
	else
	{
		GraphInter::get()->display("Este usuario no se encuentra en la lista");
		GraphInter::get()->pausa();
	}
}

void ListaPersonas::resetearUno()
{
	std::string nombre;

	GraphInter::get()->display("A quien quieres eliminar?");
	GraphInter::get()->enter(nombre);

	this->resetear(nombre);
}

void ListaPersonas::resetearTodos()
{
	for (int i = 0; i < this->length(); i++)
	{
		this->resetear(this->list[i]->nombre);
	}
}

void ListaPersonas::mostrarUno()
{
	std::string nombre;
	int ini = 0, fin = this->length() - 1, pos = 0;

	if (!this->empty())
	{
		GraphInter::get()->display("A quien quieres mostrar?");
		GraphInter::get()->enter(nombre);
		GraphInter::get()->clearConsole();

		if (this->search(nombre, pos, ini, fin))
		{
			GraphInter::get()->mostrar(this->list[pos]);
			GraphInter::get()->pausa();
		}
		else
		{
			GraphInter::get()->display("Este usuario no se encuentra en la lista");
			GraphInter::get()->pausa();
		}
	}
	else
	{
		GraphInter::get()->display("La lista esta vacia");
		GraphInter::get()->pausa();
	}
}

void ListaPersonas::mostrarTodos()
{
	if (!this->empty())
	{
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

void ListaPersonas::savelist()
{
	for (int i = 0; i <this->length(); i++)
	{
		for (int j = 0; j < COMIDAS; j++)
		{
			if (!this->list[i]->comidas[j].empty())
			{
				this->list[i]->comidas[j].save(this->list[i]->nombre + "_" + std::to_string(j) + ".txt");
			}
		}
	}
}

void ListaPersonas::loadlist()
{
	for (int i = 0; i < this->length(); i++)
	{
		for (int j = 0; j < COMIDAS; j++)
		{
			this->list[i]->comidas[j].load(this->list[i]->nombre + "_" + std::to_string(j) + ".txt");
		}
	}
}