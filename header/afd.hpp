#ifndef afd_hpp
#define afd_hpp

#include <vector>
#include <fstream>
#include "afn.hpp"

#define QTD_ESTADOS 100
#define QTD_SIMBOLOS 100

using namespace std;

class Afd{
	public:
		string estadoInicial;
		vector<string> estados;
		vector<string> simbolos;
		vector<string> estadosFinais; 
		string matriz[QTD_ESTADOS][QTD_SIMBOLOS];
		string estadoAtivo;
	public:
		Afd();
		Afd(Afn afn);
		void imprimir();
		void addEstados(string estados);
		void addEstadosFinais(string estadosFinais);
		void addSimbolos(string simbolos);
		void addTransicao(string transicao);
		void addTransicao(string inicio, string simbolo, string fim);
		void setEstadoInicial(string estadoInicial);
		void setEstadoAtivo(string estadoAtivo);
		void addEstadoTransicao(string estado);
		string getTransicao(string estado, string simbolo);
		void verificaMatriz();
		void limpaMatriz();
		bool leString(string entrada);
};

#endif