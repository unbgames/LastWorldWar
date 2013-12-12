#ifndef TILE_H
#define TILE_H

#include "Draw.h"
#include "globals.h"
#include "globalsGame.h"
#include <iostream>

class Territorio;
class Unidade;

class Tile
{
	public:
		int posX;
		int posY;
		int tipo;
    Unidade* ocupante;
    Territorio* territorio;

		Tile(int _posX, int _posY, int _tipo);
		void show(bool);
    void showCapital();
};

#endif
