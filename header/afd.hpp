class Afd{
	private:
		string estadoInicial;
		vector<string> estados;
		vector<string> simbolos;
		vector<string> estadosFinais; 
		string matriz[QTD_ESTADOS][QTD_SIMBOLOS];
	public:
		Afd();
		void imprimir();
		void addEstados(string estados);
		void addEstadosFinais(string estadosFinais);
		void addSimbolos(string simbolos);
		void addTransicao(string transicao);
		void setEstadoInicial(string estadoInicial);
};