#ifndef GRAPHINTER
#define GRAPHINTER

#include <string>

class GraphInter
{
public:

	static GraphInter* get();
	static void load();
	static void close();

	void display(std::string word);
	void display(int numero);
	void enter(std::string &word);
	void enter(int &numero);

	/*void mostrar(Persona* persona);
	void mostrar(Comida* comida);*/

	void pausa();
	int digitoEntre(int a, int b);
	void clearConsole(){ system("cls"); }

	int mainMenu();
	int secondaryMenu();

private:

	static GraphInter* inter;

	GraphInter() {}

	int update(int key, int elem, int max_elems);
	int menu(std::string elems[], int max_elems);

	void tab_word(std::string word, int pos, int cont);
	std::string tab_word(std::string word);
};

#endif

