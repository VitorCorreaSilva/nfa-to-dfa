#include "../header/afn.hpp"

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
	this->estados = picotar(estados);
}

void Afn::addEstadosFinais ( string estadosFinais ){
	this->estadosFinais = picotar(estadosFinais);
}

void Afn::addSimbolos ( string simbolos ){
	this->simbolos = picotar(simbolos);
}

void Afn::addEstadosIniciais(string estadosIniciais){
	this->estadosIniciais = picotar(estadosIniciais);
	int s = this->estadosIniciais.size();
	for (int i = 0; i < s; ++i)
	{
		estadoparaconversao.push(this->estadosIniciais[i]);
	}
}

void Afn::addTransicao ( string transicao ){
	vector<string> t = picotar(transicao);
	string inicio = t[0];
	string fim = t[1];
	string simbolo = t[2];

	if ( matriz[getIndiceEstado(inicio)][getIndiceSimbolo(simbolo)].size() == 0 ){
		matriz[getIndiceEstado(inicio)][getIndiceSimbolo(simbolo)] = fim;
	} else {
		matriz[getIndiceEstado(inicio)][getIndiceSimbolo(simbolo)] += "," + fim;
	}
}

int Afn::getIndiceEstado ( string estado ){
	int es = estados.size();
	for (int i = 0; i < es; ++i){
		if ( estados[i] == estado ) {
			return i;
		}
	}
	return 0;
}

int Afn::getIndiceSimbolo ( string simbolo ){
	int ts = simbolos.size();
	for (int i = 0; i < ts; ++i){
		if ( simbolos[i] == simbolo ) {
			return i;
		}
	}
	return 0;
}

string Afn::pegarPossibilidades ( string estado ){
	map <string, int> mapa;
	string possiveis;
	possibilidades(mapa,estado);
	for(it = mapa.begin();it != mapa.end();it++){
		if ( it != mapa.begin()){
			possiveis += ", ";
		}
		possiveis += it->first;
	}
	return possiveis;
}

void Afn::possibilidades ( map <string,int> & mapa, string estado ){
	vector <string> estadosAlcancaveis = picotar(estado);
	int ea = estadosAlcancaveis.size();
	for(int i=0;i<ea;i++){
		it = mapa.find(estadosAlcancaveis[i]);
		if ( it == mapa.end()){
			mapa.insert( pair<string,int>(estadosAlcancaveis[i],1));
			possibilidades(mapa,matriz[getIndiceEstado(estadosAlcancaveis[i])][getIndiceSimbolo("*")]);
		}
	}
}

void Afn::imprimirMatriz(){
	int es = estados.size();
	int ts = simbolos.size();
	for(int i=0;i<es;i++){
		for(int j=0;j<ts;j++){
			cout << estados[i] << "-" << simbolos[j] << " = " << matriz[getIndiceEstado(estados[i])][getIndiceSimbolo(simbolos[j])] << endl;
		}
		cout << endl;
	}
}

string Afn::distinct ( string todosestados ){
	map <string,int> mapa;
	map <string,int> :: iterator it;
	string novovalor;

	vector <string> valores = picotar(todosestados);
	int vs = valores.size();
	for(int i=0;i<vs;i++){
		it = mapa.find(valores[i]);
		if ( it == mapa.end() ){
			mapa.insert( pair<string,int>(valores[i],1));
		}
	}
	for(it = mapa.begin();it != mapa.end();it++){
		if ( it != mapa.begin()) novovalor += ", ";
		novovalor += it->first;
	}

	return novovalor;
}

string Afn::adjacentes ( string estado, string simbolo ){
	string nova = matriz[getIndiceEstado(estado)][getIndiceSimbolo(simbolo)];
	nova += "," + pegarPossibilidades(nova);
	return nova;
}

string Afn::fatiar ( string estado, string simbolo ){
	vector <string> novo = picotar(estado);
	string retorno;
	int ns = novo.size();
	for(int i=0;i<ns;i++){
		retorno += adjacentes(novo[i],simbolo) + ", "; 
	}
	retorno = distinct(retorno);
	return retorno;
}

string Afn::verificaEstado ( string estado ){
	vector <string> picotado = picotar(estado);
	string retorno = "";

	//if ( picotado.size() == 1 && picotado[0] == estadoInicial ) {
	//	retorno += "->";
	//}

	bool final = false;
	int ps = picotado.size();
	int efs = estadosFinais.size();
	for(int i=0;i<ps;i++){
		for(int j=0;j<efs;j++){
			if ( picotado[i] == estadosFinais[j]) final = true;
		}
	}
	if ( final == true ) return (retorno + "*");
	return retorno;
}

void Afn::converter () {
	map < string, int > mapa;
	map < string, int> :: iterator it;
	int ts = simbolos.size();
	while ( !estadoparaconversao.empty() ){
		string estado = estadoparaconversao.front();
		estadoparaconversao.pop();
		for(int i=0;i<ts;i++){
			if ( simbolos[i] != "*" ){
				string final = fatiar(estado,simbolos[i]);
				string query = verificaEstado(estado) + "{ " + estado + " } (" + simbolos[i] + ") = {" + final + "}";
				it = mapa.find(query);
				if ( it == mapa.end() && estado != "" ){
					estadoparaconversao.push(final);
					mapa.insert( pair<string,int> (query,1));
				}
			}
		}
	}
	for(it = mapa.begin(); it!= mapa.end();it++){
		cout << it->first << endl;
	}
}

vector<string> Afn::picotar ( string modelo ) {
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

void Afn::imprimir(){
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
		if(verificaEstadoInicial(estados[i])){
			texto += "->" + estados[i];
		}
		else{
			if(verificaEstadoFinal(estados[i])){
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

bool Afn::verificaEstadoFinal(string estado){
	int e = estadosFinais.size();
	for (int i = 0; i < e; ++i)
	{
		if(estado == estadosFinais[i]){
			return true;
		}
	}
	return false;
}

bool Afn::verificaEstadoInicial(string estado){
	int e = estadosIniciais.size();
	for (int i = 0; i < e; ++i)
	{
		if(estado == estadosIniciais[i]){
			return true;
		}
	}
	return false;
}