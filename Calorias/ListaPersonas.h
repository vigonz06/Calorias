#ifndef LISTAPERSONAS
#define LISTAPERSONAS

#include "List.h"
#include "Persona.h"

class ListaPersonas : public List <Persona>
{
public:
	
	void añadir();
	void editar(ListaAlimentos* lista);
	void eliminar();

	void resetear(std::string nombre);
	void resetearUno();
	void resetearTodos();

	void mostrarUno();
	void mostrarTodos();

	void savelist();
	void loadlist();
};

#endif
