#ifndef LISTACOMIDA
#define LISTACOMIDA

#include "List.h"
#include "Comida.h"

class ListaComida : public List <Comida>
{
public:
	
	bool insert(Comida* nueva);
};

#endif

