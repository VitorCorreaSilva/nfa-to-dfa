#include "../header/afn.hpp"

int main () {
	Afn automato("entrada");

	vector<string> e;

	int t = automato.estados.size();
	for (int i = 0; i < t; ++i)
	{
		cout << automato.estados[i] << endl;
	}



	//automato.imprimir();
}