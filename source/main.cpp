#include "../header/afn.hpp"

int main () {
	Afn automato;
	string qe, ei, ef, alf,tri,trf,trs;
	char fim='s';

	cout << "Digite os estados ('q1,q2,q3....')" << endl;
	cin >> qe;
	cout << "Digite estado inicial " << endl;
	cin >> ei;
	cout << "Digite estado(s) final(s)" << endl;
	cin >> ef;
	cout << "Digite o alfabeto (* reepresenta vazio)" << endl;
	cin >> alf;
	automato.addEstados(qe);
	automato.setEstadoInicial(ei);
	automato.addEstadosFinais(ef);
	automato.addSimbolos(alf);

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
