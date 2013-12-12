#ifndef GLOBALSGAME_H
#define GLOBALSGAME_H

#include "SDL/SDL.h"
#include "Cenario.h"
#include "ClasseUnidade.h"
#include "Unidade.h"
#include "Territorio.h"
#include "Tile.h"

#define LINHAS_MAPA 24
#define COLUNAS_MAPA 33

//cenarios
enum {
	TELA_INICIAL,
	MENU_INICIAL,
	INICIO,	
	PREPARACAOJOGO,
	NIVEL,
	INSTRUCOES,
	OPCOES,
	CREDITOS,
	LOADING			//trabalhar nesta para fazer a proxima entrega
};

//carregando cores dos tiles do mapa-mundi
enum {
	AZUL,		//oceano
	MARROM,		//terra
	VERDE,		//floresta
	AMARELO,	//OURO
	BRANCO,		//fronteira agua e terra
	VERMELHO,  //PETROLEO
	CINZA, //FERRO

	PRETO		//unidade
};

//nomeando de acordo com as cores dos tiles do mapa-mundi
enum {
	OCEANO,		//oceano
	TERRA,		//terra
	FLORESTA,	//floresta
	MINA_OURO,	//OURO
	FRONTEIRA,	//fronteira agua e terra
	PETROLEO,   //PETROLEO
	MINA_FERRO,	//FERRO

	UNIDADE		//unidade
};

//tipo de ambiente que pode se mover
enum {
	TERRESTRE,
	AQUATICO,
	QUALQUER_AMBIENTE
};

//modo de apresentacao desse mapa de bits
enum {
	MODO_NORMAL,
	MODO_QUADRADOS_PREENCHIDOS
	//MODO_QUADRADOS,
	//MODO_CIRCULOS
};

extern int scenarioAtual;

extern Uint32 cores[];		//correspondendo as cores definidas no enum

extern SDL_Surface* transparentSurface;

extern int modo;

extern Unidade* unidadeSelecionada;
extern Nacao* nacaoSelecionada;
extern Territorio* territorioSelecionado;

extern ClasseUnidade* soldado;
extern ClasseUnidade* canhao;
extern ClasseUnidade* navio;
extern ClasseUnidade* aviao;

//The surfaces that will be used
extern SDL_Surface *logoEmpresa;
extern SDL_Surface *logoJogo;
extern SDL_Surface *logoRecursos;
extern SDL_Surface *classificacaoIndicativa;
extern SDL_Surface *menu;
extern SDL_Surface *mapa;
extern SDL_Surface *escolhaNacao;
extern SDL_Surface *nivel;
extern SDL_Surface *telaInstrucoes;
extern SDL_Surface *telaOpcoes;
extern SDL_Surface *telaCreditos;
extern SDL_Surface *telaLoading;
extern SDL_Surface *loading;


extern SDL_Surface *messageRecursos;
extern SDL_Surface *messageUnidades;
extern SDL_Surface *messageTerritorios;
extern SDL_Surface *messageGameOver;
extern SDL_Surface *messageGeneralInfo;

extern SDL_Surface *opcaoJogar;
extern SDL_Surface *opcaoInstrucoes;
extern SDL_Surface *opcaoOpcoes;
extern SDL_Surface *opcaoSair;
extern SDL_Surface *opcaoCreditos;
extern SDL_Surface *timeEua;
extern SDL_Surface *timeSiria;
extern SDL_Surface *opcaoVoltar;
extern SDL_Surface *opcaoNivel1;
extern SDL_Surface *opcaoNivel2;
extern SDL_Surface *opcaoNivel3;
extern SDL_Surface *opcaoNivel4;
extern SDL_Surface *opcaoNivel5;
extern SDL_Surface *textoCompleto;
extern SDL_Surface *creditosCompleto;
extern SDL_Surface *textoAudio;
extern SDL_Surface *textoSoundT;
extern SDL_Surface *textoSoundE;

extern char scoreRecursosNacao[300];
extern char scoreUnidadesNacao[300];	
extern char scoreTerritoriosNacao[300];	
extern char scoreGameOver[300];	
extern char scoreGeneralInfo[300];

extern char instrucoes[20];
extern char jogar[20];
extern char opcoes[20];
extern char sair[20];
extern char creditos[20];
extern char eua[20];
extern char siria[20];
extern char voltar[20];
extern char nivel1[20];
extern char nivel2[20];
extern char nivel3[20];
extern char nivel4[20];
extern char nivel5[20];
extern char texto[300];
extern char creditosTexto[300];
extern char audio[20];
extern char soundT[20];
extern char soundE[20];

//carregando imagem das unidades
extern SDL_Surface *civilizationUnits;

extern Cenario* cenario;

/*
//inicializando uma unidade pra testar
extern Unidade* unit1;
extern Unidade* unit2;
extern Unidade* unidadeSelecionada;
*/

/*	FIM	*/

#endif
