#include "../header/afn.hpp"

int main () {
	Afn automato;
	string qe, ei, ef, cadeia,tri,trf,trs;
	char fim='s';

	cout << "Digite a quantidade de estados " << endl;
	cin >> qe;
	cout << "Digite estado inicial " << endl;
	cin >> ei;
	cout << "Digite estado(s) final(s)" << endl;
	cin >> ef;
	cout << "Digite a cadeia" << endl;
	cin >> cadeia;
	automato.addEstados(qe);
	automato.setEstadoInicial(ei);
	automato.addEstadosFinais(ef);
	automato.addSimbolos(cadeia);

	while(fim == 's'){
    cout << "Digite as transicoes (De - Para - Simbolo)" << endl;
	cin >> tri;
	cin >> trf;
	cin >> trs;
	automato.addTransicao(tri,trf,trs);
	cout << "Digite s para nova n para finalizar " << endl;
	cin >> fim;	
	system("clear");
	};
	

	automato.converter();
}