#ifndef LISTAALIMENTOS
#define LISTAALIMENTOS

#include "List.h"
#include "Comida.h"

class ListaAlimentos : public List <Alimento>
{
public:

	void a�adir();
	void editar();
	void eliminar();

	void mostrarUno();
	void mostrarTodos();
};

#endif

