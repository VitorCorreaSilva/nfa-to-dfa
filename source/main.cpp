#include "../header/afn.hpp"
#include "../header/afd.hpp"
#include "../header/funcoes.hpp"


int main () {
	Funcoes f;
	string text;
	Afn afn("entrada");

	Afd afd(afn);

	afd.verificaMatriz();

	afd.imprimir();	



	
}