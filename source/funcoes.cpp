#include "../header/funcoes.hpp"

Funcoes::Funcoes(){}

vector<string> Funcoes::picotar(string modelo){
	vector <string> retorno;
	string aux = "";
	int ms = modelo.size();

	for (int i = 0; i < ms; ++i){
		if ( modelo[i] == ',' || modelo[i] == ' ' ){
			if ( aux != "" ) {
				retorno.push_back(aux);
			}			
			aux = "";
		} else { 
			aux += modelo[i];
		}

		int var_ms = modelo.size() - 1;
		if ( i == var_ms ){
			if ( aux != "" ){
				retorno.push_back(aux);
			} 
		}
	}
	return retorno;
}

int Funcoes::getIndice(vector<string> vetor, string texto){

	int vs = vetor.size();
	for (int i = 0; i < vs; ++i){
		if ( vetor[i] == texto ) {
			return i;
		}
	}
	return 0;
}

bool Funcoes::verificaEstadoFinal(vector<string> estadosFinais, string estado){
	int e = estadosFinais.size();
	for (int i = 0; i < e; ++i)
	{
		if(estado == estadosFinais[i]){
			return true;
		}
	}
	return false;
}

bool Funcoes::verificaEstadoInicial(vector<string> estadosIniciais, string estado){
	int e = estadosIniciais.size();
	for (int i = 0; i < e; ++i)
	{
		if(estado == estadosIniciais[i]){
			return true;
		}
	}
	return false;
}

bool Funcoes::verificarEstados(vector<string> estados, string estado){
	int e = estados.size();
	for (int i = 0; i < e; ++i){
		if (estados[i] == estado){
			return true;
		}
	}

	return false;
}