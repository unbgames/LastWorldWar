#include "globalsGame.h"

int scenarioAtual = TELA_INICIAL;
Uint32 cores[] = {0x0000FF, 0x9F6F2F, 0x00CC00, 0xFFFF00, 0xFFFFFF, 0xFF0000, 0xC0C0C0, 0x000000};		//correspondendo as cores definidas no enum
SDL_Surface* transparentSurface = NULL;
int modo = MODO_NORMAL;

Unidade* unidadeSelecionada = NULL;
Nacao* nacaoSelecionada = NULL;
Territorio* territorioSelecionado = NULL;

ClasseUnidade* soldado = NULL;
ClasseUnidade* canhao = NULL;
ClasseUnidade* navio = NULL;
ClasseUnidade* aviao = NULL;

//The surfaces that will be used
SDL_Surface *logoEmpresa = NULL;
SDL_Surface *logoJogo = NULL;
SDL_Surface *logoRecursos = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *classificacaoIndicativa = NULL;
SDL_Surface *mapa = NULL;
SDL_Surface *escolhaNacao = NULL;
SDL_Surface *nivel = NULL;
SDL_Surface *telaInstrucoes = NULL;
SDL_Surface *telaOpcoes = NULL;
SDL_Surface *telaCreditos = NULL;
SDL_Surface *telaLoading = NULL;
SDL_Surface *loading = NULL;

SDL_Surface *messageRecursos = NULL;
SDL_Surface *messageUnidades = NULL;
SDL_Surface *messageTerritorios = NULL;
SDL_Surface *messageGameOver = NULL;
SDL_Surface *messageGeneralInfo = NULL;

SDL_Surface *opcaoJogar = NULL;
SDL_Surface *opcaoInstrucoes = NULL;
SDL_Surface *opcaoOpcoes = NULL;
SDL_Surface *opcaoSair = NULL;
SDL_Surface *opcaoCreditos = NULL;
SDL_Surface *textoCompleto = NULL;

SDL_Surface *timeEua = NULL;
SDL_Surface *timeSiria = NULL;
SDL_Surface *opcaoVoltar = NULL;
SDL_Surface *opcaoNivel1 = NULL;
SDL_Surface *opcaoNivel2 = NULL;
SDL_Surface *opcaoNivel3 = NULL;
SDL_Surface *opcaoNivel4 = NULL;
SDL_Surface *opcaoNivel5 = NULL;
SDL_Surface *creditosCompleto = NULL;
SDL_Surface *textoAudio = NULL;
SDL_Surface *textoSoundT = NULL;
SDL_Surface *textoSoundE = NULL;

char scoreRecursosNacao[300];
char scoreUnidadesNacao[300];	
char scoreTerritoriosNacao[300];
char scoreGameOver[300];	
char scoreGeneralInfo[300];

char instrucoes[20];
char jogar[20];
char opcoes[20];
char sair[20];
char creditos[20];
char eua[20];
char siria[20];
char voltar[20];
char nivel1[20];
char nivel2[20];
char nivel3[20];
char nivel4[20];
char nivel5[20];
char texto[300];
char creditosTexto[300];
char audio[20];
char soundT[20];
char soundE[20];

//carregando imagem das unidades
SDL_Surface *civilizationUnits = NULL;

Cenario* cenario = NULL;

