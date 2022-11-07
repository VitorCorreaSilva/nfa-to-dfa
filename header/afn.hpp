#ifndef afn_hpp
#define afn_hpp

#include <vector>
#include <fstream>

#define QTD_ESTADOS 100
#define QTD_SIMBOLOS 100

using namespace std;

class Afn{
	public:
		vector<string> estadosIniciais;
		vector<string> estados;
		vector<string> simbolos;
		vector<string> estadosFinais; 
		string matriz[QTD_ESTADOS][QTD_SIMBOLOS];
						
	public:
		Afn();
		Afn(string arquivo);
		void addEstados(string estados);
		void addEstadosFinais(string estadosFinais);
		void addSimbolos(string simbolos);
		void addTransicao(string transicao);
		void addEstadosIniciais(string estadosIniciais);
		void imprimir();
		string getTransicao(string estado, string simbolo);
		void converter();
};

#endif