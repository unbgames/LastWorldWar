#ifndef NACAO_H
#define NACAO_H
#include "globalsGame.h" 
#include <list> 

class Unidade;
class Territorio;
class ClasseUnidade;

class Nacao
{
	public: 
		list <Unidade*> exercito;
		list <Territorio*> territorios;
		
		int petroleo;
		int madeira;
		int ouro;
		int ferro;

	
		int qtdNacao[4];

		string nome;
		Uint32 cor;

		Nacao(int, int, int, int, string, Uint32);
		void init();
		void exercitoAdd(ClasseUnidade*, Territorio*, int, int);
		void exercitoPop();
		void carregaScore();
		void contarExercito();
		int contarTerritorios();
		void coletar();
		void finalize();
		void atualizaQuadroExercito();
};

#endif
