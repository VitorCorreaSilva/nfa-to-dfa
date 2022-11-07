#include "../header/afd.hpp"
#include "../header/funcoes.hpp"

Afd::Afd(){}

Afd::Afd(Afn afn){
	estadosFinais = afn.estadosFinais;
	estadoInicial = afn.estadosIniciais[0];
	simbolos = afn.simbolos;
	estados = afn.estados;

	int e = estados.size();
	int s = simbolos.size();

	for (int i = 0; i < e; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			matriz[i][j] = afn.matriz[i][j];
		}
	}
}


void Afd::addEstados ( string estados ){
	Funcoes f;
	this->estados = f.picotar(estados);
}

void Afd::addEstadosFinais ( string estadosFinais ){
	Funcoes f;
	this->estadosFinais = f.picotar(estadosFinais);
}

void Afd::addSimbolos ( string simbolos ){
	Funcoes f;
	this->simbolos = f.picotar(simbolos);
}

void Afd::setEstadoInicial(string estadoInicial){
	this->estadoInicial = estadoInicial;
}

void Afd::setEstadoAtivo(string estadoAtivo){
	this->estadoAtivo = estadoAtivo;
}

void Afd::addTransicao(string transicao){
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

void Afd::addTransicao(string inicio, string simbolo, string fim){
	Funcoes f;
	if ( matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)].size() == 0 ){
		matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)] = fim;
	} else {
		matriz[f.getIndice(estados, inicio)][f.getIndice(simbolos, simbolo)] += "," + fim;
	}
}

void Afd::imprimir(){
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
		if(estadoInicial == estados[i]){
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

void Afd::addEstadoTransicao(string estado){
	Funcoes f;
	string r = "";
	int s = simbolos.size();
	for (int i = 0; i < s; i++)
	{
		vector<string> aux = f.picotar(estado);
		int a = aux.size();
		string antiga = "";
		for (int j = 0; j < a; j++)
		{	
			string nova = getTransicao(aux[j], simbolos[i]);
			if(antiga != nova){
				if(j == 0){
					r = nova;
					antiga = r;
				}
				else if(nova != ""){
					r += "," + nova;
				}
			}

			if(f.verificarEstados(estadosFinais, nova)){
				estadosFinais.push_back(r);
			}
		}
		addTransicao(estado, simbolos[i], r);
	}
	verificaMatriz();
}

string Afd::getTransicao(string estado, string simbolo){
	Funcoes f;
	int e = f.getIndice(estados, estado);
	int s = f.getIndice(simbolos, simbolo);

	return matriz[e][s];
}

void Afd::verificaMatriz(){
	Funcoes f;
	int e = estados.size();
	int s = simbolos.size();
	for (int i = 0; i < e; i++)
	{
		for (int j = 0; j < s; j++)
		{
			string simbolo = simbolos[j];
			string estado = matriz[i][j];
			vector<string> ep = f.picotar(estado);
			int eps = ep.size();
			if(eps > 1 && eps <= 3 && !f.verificarEstados(estados, estado)){
				estados.push_back(estado);
				addEstadoTransicao(estado);
			}
		}
	}
}

void Afd::limpaMatriz(){
	Funcoes f;
	int e = estados.size();
	int s = simbolos.size();
	string ret[QTD_ESTADOS][QTD_SIMBOLOS];

	for (int i = 0; i < e; ++i)
	{
		for (int j = 0; j < s; ++j)
		{
			string nova = getTransicao(estados[i], simbolos[j]);
			if(nova != ""){
				ret[i][j] = nova;
			}
		}
	}	
}

bool Afd::leString(string entrada){
	Funcoes f;
	int tam = entrada.size();
	setEstadoAtivo(estadoInicial);

	for (int i = 0; i < tam; ++i)
	{	
		string en = (string)entrada[i];
		if(f.verificarEstados(simbolos, en)){
			cout << "Simbolo não pertence ao alfabeto";
		}
		else{
			string trans = getTransicao(estadoAtivo, en);
			cout << estadoAtivo << " -> " << entrada[i] << " -> " << trans << endl; 
			setEstadoAtivo(trans);
		}
	}

	if(f.verificarEstados(estadosFinais, estadoAtivo)){
		cout << "String aceita" << endl;
	}
	else{
		cout << "String não aceita" << endl;
	}
}