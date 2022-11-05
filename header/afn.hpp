#include <vector>
#include <fstream>

#include <iostream>
#include <map>
#include <queue>

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

		vector<string> picotar(string modelo);
		int getIndiceEstado(string estado);
		int getIndiceSimbolo(string simbolo);
		bool verificaEstadoFinal(string estado);
		bool verificaEstadoInicial(string estado);
				
		vector<string> AFD;
		map<string,int> ::iterator it;
		queue<string> estadoparaconversao;		
		
	public:
		Afn();
		Afn(string arquivo);
		void imprimir();
		void addEstados(string estados);
		void addEstadosFinais(string estadosFinais);
		void addSimbolos(string simbolos);
		void addTransicao(string transicao);
		void addEstadosIniciais(string estadosIniciais);
		

		string pegarPossibilidades(string estado);
		void possibilidades(map <string,int> &mapa, string estado);
		void imprimirMatriz();
		string distinct(string todosestados);
		string adjacentes(string estado, string simbolo);
		string fatiar(string estado, string simbolo);
		string verificaEstado(string estado);

		void converter();
};