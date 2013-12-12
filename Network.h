#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "Nacao.h"
#include "Unidade.h"

#define MAXLEN 10240
#define MAXFILA 24

using namespace std;

class Nacao;

class Unidade;

class Network
{
  public:
    char *ipServidor;
    short porta;
    char backspace;

    //Flag de atuação...
    bool host;
    char msg[MAXLEN],animacao[6];
    int loop;

    int ultimoFila, primeiroFila;
    char mensagens[MAXFILA][32];

    Unidade* unidadeSelecionada;
    Unidade* unidadeAlvo;

    TCPsocket conexao;
    SDLNet_SocketSet socketSet;

  Network();
  void initializeNetwork();
  void lerComando();
  bool lerTCP(int, char*);
  bool escreveTCP(int);
  bool escreveTCPString(string);

  bool enviaJogoInicial(int, int);
  bool recebeJogoInicial(int&, int&);
  void pushMovimento(int, int, char);
  bool recebeJogada(Nacao*);
  bool enviaJogada();
  void selecionarUnidadeNacao(Nacao, int , int );
};
#endif