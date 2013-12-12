#ifndef TERRITORIO_H
#define TERRITORIO_H

#include "Nacao.h"
#include "ClasseUnidade.h"
#include "globals.h"
#include "globalsGame.h"
#include <iostream>
#include <list> 

class Tile;

class Territorio
{
  public:
    list <Tile*> tiles;
    Nacao* nacao;
	string nome;
	
	int pontosProducao;

    Territorio(string);
    void coletar();
    void serConquistado(Nacao* _nacao);
    void addTile(Tile* tile);
    void mostrarCapital();
	void criarUnidade(ClasseUnidade* classeUnidade);
};

#endif
