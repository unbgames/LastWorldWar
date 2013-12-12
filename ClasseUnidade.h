#ifndef CLASSEUNIDADE_H
#define CLASSEUNIDADE_H

#include "Draw.h"
#include "globals.h"
#include "globalsGame.h"
#include <string>

class ClasseUnidade
{
	public:
		string nome;
		int qtdMovimentos;	
		int ambiente;			//0 terra, 1 agua, 2 ambos	
		int forca;

		int custoFerro;
		int custoOuro;
		int custoMadeira;
		int custoPetroleo;

		int custoTurnos;

		ClasseUnidade(string, int, int, int,  int, int, int, int,  int);
};

#endif
