#ifndef LISTAALIMENTOS
#define LISTAALIMENTOS

#include "List.h"
#include "Comida.h"

class ListaAlimentos : public List <Alimento>
{
public:

	void añadir();
	void editar();
	void eliminar();

	void mostrarUno();
	void mostrarTodos();
};

#endif

