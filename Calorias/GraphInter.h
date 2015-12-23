#ifndef GRAPHINTER
#define GRAPHINTER

#include <string>
#include "Persona.h"
#include "Comida.h"

class GraphInter
{
public:

	static GraphInter* get();

	void display(std::string word);
	void display(int numero);
	void enter(std::string &word);
	void enter(int &numero);

	std::string minus(std::string word);
	int traducir();
	bool traducir2();
	std::string traducir(int comida);
	std::string traducir2(bool solid);

	void mostrar(Persona* persona);
	void mostrar(Comida* comida);
	void mostrar(Alimento* alimento);

	void pausa();
	void clearConsole(){ system("cls"); }

	int mainMenu();
	int userMenu();
	int foodMenu();
	int multMenu();

private:

	static GraphInter* inter;

	GraphInter() {}

	int update(int key, int elem, int max_elems);
	int menu(std::string elems[], int max_elems);

	void tab_word(std::string word, int pos, int cont);
	std::string tab_word(std::string word);
};

#endif

