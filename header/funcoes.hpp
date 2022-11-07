#ifndef funcoes_hpp
#define funcoes_hpp

#include <vector>
#include <iostream>

using namespace std;

class Funcoes{
	public:
		Funcoes();
		vector<string> picotar(string modelo);
		int getIndice(vector<string> vetor, string texto);
		bool verificaEstadoFinal(vector<string> estadosFinais, string estado);
		bool verificaEstadoInicial(vector<string> estadosIniciais, string estado);
		bool verificarEstados(vector<string> estados, string estado);
};

#endif