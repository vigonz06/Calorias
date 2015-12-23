#include "ListaComida.h"

bool ListaComida::insert(Comida* nueva)
{
	if (this->full()) this->resize(this->dim * 3 / 2);

	this->list[this->counter] = nueva;
	this->counter++;

	return true;
}
