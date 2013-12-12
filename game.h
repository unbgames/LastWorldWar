#ifndef GAME_H
#define GAME_H

#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Tile.h"
#include "Cenario.h"
#include "Unidade.h"
#include "globals.h"
#include "globalsGame.h"
#include "ImageHandlerSDL.h"
#include "FontHandler.h"
#include "Timer.h"
#include "AudioHandler.h"
#include "Draw.h"
#include <iostream>
#include <thread>

using namespace std;

extern int initializeCenario1();
extern int finalizeCenario1();

extern int initialize();
extern int finalize();

//outras funcoes (rede, tempo)
extern int updateTime();
extern int receiveNetworkMessages();

//get inputs
extern int get_inputs();

//funcao menu
extern void selecionarMenu();
extern void selecionaNacao();
extern void selecionarNivel();
extern void selecionarOpcoes();
extern void carregarLoading();

//do Logic
extern int tratarColisoes();
extern int atualizarEstados();
extern int do_logic();	

//do drawing
extern int do_drawing();

//outras funcoes (som, rede, tempo)
extern int sound();
extern int sendNetworkMessages();

#endif
