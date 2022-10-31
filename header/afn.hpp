#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define QTD_ESTADOS 100
#define QTD_SIMBOLOS 100

using namespace std;

class Afn{
	private:
		string estadoInicial;
		vector<string> estados;
		vector<string> terminais;
		vector<string> estadosfinais; 
		map<string,int> ::iterator it;
		string matriz[QTD_ESTADOS][QTD_SIMBOLOS];
		vector<string> AFD;
		queue<string> estadoparaconversao;		
		vector<string> picotar (string modelo );
	public:
		Afn();
		void addEstados(string conjuntoDeEstados);
		void addEstadosFinais(string conjuntoDeEstadosFinais);
		void addSimbolos(string conjuntoDeSimbolos);
		void setEstadoInicial(string estadoInicial);
		void addTransicao(string inicio, string fim, string simbolo);
		int getIndiceEstado(string estado);
		int getIndiceSimbolo(string simbolo);
		string pegarPossibilidades(string estado);
		void possibilidades(map <string,int> &mapa, string estado);
		void imprimirMatriz();
		string distinct(string todosestados);
		string adjacentes(string estado, string simbolo);
		string fatiar(string estado, string simbolo);
		string verificaEstado(string estado);
		void converter();
};