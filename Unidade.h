#ifndef UNIDADE_H
#define UNIDADE_H

#include "Draw.h"
#include "globals.h"
#include "globalsGame.h"
#include <string>
#include <list>

class ClasseUnidade;
class Nacao;
class Tile;

class Unidade
{
	public:
		int posX;	//tile X do mapa onde atualmente habita
		int posY;	//tile Y do mapa onde atualmente habita
//		int tipo;	//aviao,navio,soldado,canhao,etc...
		ClasseUnidade* tipo;
		Nacao* nacao;

		int qtdMovimentos;
		list<Unidade*>unidadesGuardadas;

		int quadroAnimacao;
		int tipoAnimacao;		//0 parado, 1 sequencia, 2 continua ate comando de parar

		bool isDead;
		bool selecionado;

		Unidade(int, int, ClasseUnidade*, Nacao*);
		int show();
		int attack(Unidade *); 
		bool canMove(Tile* tileDestino);
		void atualizaAnimacao();
		void finalize();
};

#endif
