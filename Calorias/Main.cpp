#include "ListaAlimentos.h"
#include "ListaPersonas.h"
#include "GraphInter.h"

void main()
{
	ListaAlimentos* alimentos = new ListaAlimentos;
	ListaPersonas usuarios;

	int opcion1, opcion2, opcion3;

	alimentos->load("Alimentos.txt");
	usuarios.load("Personas.txt");
	usuarios.loadlist();

	do
	{
		GraphInter::get()->clearConsole();
		opcion1 = GraphInter::get()->mainMenu();
		GraphInter::get()->clearConsole();

		if (opcion1 == 0)
		{
			do
			{
				GraphInter::get()->clearConsole();
				opcion2 = GraphInter::get()->userMenu();
				GraphInter::get()->clearConsole();

				if (opcion2 == 0)
				{
					usuarios.añadir();
				}
				else if (opcion2 == 1)
				{
					usuarios.editar(alimentos);
				}
				else if (opcion2 == 2)
				{
					do
					{
						GraphInter::get()->clearConsole();
						opcion3 = GraphInter::get()->multMenu();
						GraphInter::get()->clearConsole();

						if (opcion3 == 0)
						{
							usuarios.resetearUno();
						}
						else if (opcion3 == 1)
						{
							usuarios.resetearTodos();
						}
					} while (opcion3 != 2);
				}
				else if (opcion2 == 3)
				{
					usuarios.eliminar();
				}
				else if (opcion2 == 4)
				{
					do
					{
						GraphInter::get()->clearConsole();
						opcion3 = GraphInter::get()->multMenu();
						GraphInter::get()->clearConsole();

						if (opcion3 == 0)
						{
							usuarios.mostrarUno();
						}
						else if (opcion3 == 1)
						{
							usuarios.mostrarTodos();
						}
					} while (opcion3 != 2);
				}
			} while (opcion2 != 5);
		}
		else if (opcion1 == 1)
		{
			do
			{
				GraphInter::get()->clearConsole();
				opcion2 = GraphInter::get()->foodMenu();
				GraphInter::get()->clearConsole();

				if (opcion2 == 0)
				{
					alimentos->añadir();
				}
				else if (opcion2 == 1)
				{
					alimentos->editar();
				}
				else if (opcion2 == 2)
				{
					alimentos->eliminar();
				}
				else if (opcion2 == 3)
				{
					do
					{
						GraphInter::get()->clearConsole();
						opcion3 = GraphInter::get()->multMenu();
						GraphInter::get()->clearConsole();

						if (opcion3 == 0)
						{
							alimentos->mostrarUno();
						}
						else if (opcion3 == 1)
						{
							alimentos->mostrarTodos();
						}
					} while (opcion3 != 2);
				}
			} while (opcion2 != 4);
		}
	} while (opcion1 != 2);

	alimentos->save("Alimentos.txt");
	usuarios.save("Personas.txt");
	usuarios.savelist();

	delete alimentos;
}