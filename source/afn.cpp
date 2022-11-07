#include "../header/afn.hpp"
#include "../header/funcoes.hpp"

Afn::Afn(){}

Afn::Afn(string caminho){
	ifstream file;
	string entrada;

	file.open(caminho);

	getline(file, entrada);
    this->addEstados(entrada);

    getline(file, entrada);
    this->addEstadosIniciais(entrada);

    getline(file, entrada);
    this->addEstadosFinais(entrada);

    getline(file, entrada);
    this->addSimbolos(entrada);

	while(!file.eof()){
    	getline(file, entrada);
		this->addTransicao(entrada);
	}
}

void Afn::addEstados ( string estados ){
	Funcoes f;
	this->estados = f.picotar(estados);
}

void Afn::addEstadosFinais ( string estadosFinais ){
	Funcoes f;
	this->estadosFinais = f.picotar(estadosFinais);
}

void Afn::addSimbolos ( string simbolos ){
	Funcoes f;
	this->simbolos = f.picotar(simbolos);
}

void Afn::addEstadosIniciais(string estadosIniciais){
	Funcoes f;
	this->estadosIniciais = f.picotar(estadosIniciais);
}

void Afn::addTransicao ( string transicao ){
	Funcoes f;
	vector<string> t = f.picotar(transicao);
	string inicio = t[0];
	string fim = t[1];
	string simbolo = t[2];

	if ( matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)].size() == 0 ){
		matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)] = fim;
	} else {
		matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)] += "," + fim;
	}
}

void Afn::imprimir(){
	Funcoes f;
	string texto = "";
	int s = simbolos.size();
	int e = estados.size();
	
	for (int i = 0; i < s; ++i)
	{
		texto += "\t " + simbolos[i];
	}
	texto += "\n";

	for (int i = 0; i < e; ++i)
	{
		if(f.verificaEstadoInicial(estadosIniciais, estados[i])){
			texto += "->" + estados[i];
		}
		else{
			if(f.verificaEstadoFinal(estadosFinais, estados[i])){
				texto += "*" + estados[i];
			}
			else{
				texto += estados[i];
			}
		}

		for (int j = 0; j < s; ++j)
		{
			texto += "\t" + matriz[i][j] ;
		}
		texto += "\n";
	}

	cout << texto;
}

string Afn::getTransicao(string estado, string simbolo){
	Funcoes f;
	int e = f.getIndice(estados, estado);
	int s = f.getIndice(simbolos, simbolo);

	return matriz[e][s];
}