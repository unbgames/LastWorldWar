#include <iostream>
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "Network.h"
#include "Nacao.h"
#include "Unidade.h"
#define DEBUG 1


void Network::selecionarUnidadeNacao(Nacao nacao, int tileX, int tileY)
{
    for(list<Unidade *>::iterator it1 = nacao.exercito.begin(); it1 != nacao.exercito.end(); it1++) 
    {
       //(*(*it1)).isDead = true;

      if(tileX == (*(*it1)).posX && tileY == (*(*it1)).posY)
      {
        if(unidadeSelecionada==0)
        {
          unidadeSelecionada = (*it1);
          
          if ((*(*it1)).isDead == false)
          {
            (*unidadeSelecionada).selecionado = true; 
          }     
        }         
        else
        {
          (*unidadeSelecionada).selecionado = false;          
          unidadeAlvo = (*it1);
          (*unidadeSelecionada).attack(unidadeAlvo);
          unidadeSelecionada = 0;         
          unidadeAlvo = 0;  
        }
      }
    }
}


 Network::Network(){
    //IP do servidor
    ipServidor = (char *) "127.0.0.1";
    //Enderço do Dynamic DNS para jogar online. Funciona na rede da casa da Gabriela. Atualizar o IP no site dyndns.com.br
  //  ipServidor = (char *) "thelastworldwar.game-host.org";
    porta = 9999;
    backspace = 8;
    animacao[0] = '|';
    animacao[1] = '/';
    animacao[2] = '-';
    animacao[3] = '|';
    animacao[4] = '\\';
    animacao[5] = '-';

    // animacao[6] = (char*) {'|','/','-','|','\\','-'};
    loop = 0;


    ultimoFila = 0;
    primeiroFila = 0;

    socketSet = SDLNet_AllocSocketSet(1);
    }

  string ConverteParaCaracter(int tamanho) {
    char caracteres[4];
    for (int i=3;i>-1;i--) {
      int resto = tamanho % 10;
      caracteres[i] = '0' + resto; 
      tamanho = tamanho / 10;
    }
    string volta(caracteres,4);
    return volta;
  }

  bool Network::recebeJogada(Nacao* nacaoInimigo) {
    //cout << "<RecebeJogada" << endl;
    // Verifica se tem algo para receber
    int numReady = SDLNet_CheckSockets(socketSet, 0);
    if (numReady == -1) {
      cout << "Erro : " <<  SDLNet_GetError() << endl;
      // Finalizar
      SDLNet_TCP_Close(conexao);
      SDLNet_TCP_DelSocket(socketSet,conexao);
      exit(9);
    }
    if (!numReady) {
      return true;
    }
    // Deve vir um D
    lerComando();
    if (msg[0] == 'F') {
      // O outro lado pulou fora
      SDLNet_TCP_Close(conexao);
      SDLNet_TCP_DelSocket(socketSet,conexao);
      quit = true;
      return true;
    }
    if (msg[0] != 'D') {
      // ue?? tá doidao o outro lado...
      return false;
    }
    // le tamanho
    if (lerTCP(4,msg+1)) {
      int tamDados = 0;
      for (int i=1;i<5;i++) {
        tamDados = tamDados * 10 + (msg[i] - '0');
      }
      if (lerTCP(tamDados,msg+5)){
        if(msg[5] == 'M'){ // Movimentaçao
          int x = 0, y = 0, pos = 7;
          char evento;
          // calcula x
          for (int i=6;i<tamDados+5;i++) {
            if (msg[i] == 'Y') {
              break;
            }
            pos += 1;
            x = x * 10 + (msg[i] - '0');
          }
          // calcula Y
          for (int i=pos;i<(tamDados+4);i++) {
            y = y * 10 + (msg[i] - '0');
          }
          evento = msg[tamDados+4];
          cout << "RecebeJogada x (" << x << ") y (" << y << ") evento (" << evento << ")" << endl;
          
          unidadeSelecionada = NULL;
          selecionarUnidadeNacao((*nacaoInimigo), x, y);
          if (unidadeSelecionada != NULL) {
            if (evento == 'a') {
              (*unidadeSelecionada).posX -= 1;
            }else if (evento == 'd') {
              (*unidadeSelecionada).posX += 1;
            }else if (evento == 'w') {
              (*unidadeSelecionada).posY -= 1;
            }else if (evento == 's') {
              (*unidadeSelecionada).posY += 1;
            }else {
              cout << "evento invalido para movimento de unidade" << endl;
            }
          } else {
            cout << "Nao encontrei unidade a movimentar" << endl;
          }
          

          return true;
        }else if (msg[5] == 'T') { // Passa o turno
          meuTurno = true;
          unidadeSelecionada = NULL;
          unidadeAlvo = NULL; 
        } 
      }
    }  
    return false;
  }

  bool Network::enviaJogada() {
    //cout << "<EnviaJogada" << endl;
    while (ultimoFila!=primeiroFila) {
      cout << "EnviaJogada primeiroFila (" << primeiroFila << ") ultimoFila (" << primeiroFila << endl;
      int tamanho = mensagens[primeiroFila][0];
      string texto(mensagens[primeiroFila]+1,tamanho);
      stringstream sstm;
      sstm << "D" << ConverteParaCaracter(tamanho) << texto;
      if (!escreveTCPString(sstm.str())) {
        return false;
      }

      primeiroFila += 1;
      if (primeiroFila==MAXFILA) {
        primeiroFila = 0;
      }
    }
    return true;
  }

  void Network::pushMovimento(int x, int y, char evento){
    cout << "Push Movimento  X: " << x << " Y: " << y << " Evento: " << evento << endl;
    stringstream sstm;
    sstm << "M" << x << "Y" << y << evento;
    strcpy(mensagens[ultimoFila]+1,sstm.str().c_str());
    mensagens[ultimoFila][0] = (char) sstm.str().size();
    cout << "ultimoFila (" << ultimoFila << ") Tamanho (" << (int) mensagens[ultimoFila][0] << ") Mensagem (";
    for (int i=1; i<((int) mensagens[ultimoFila][0])+1;i++) {
      cout << mensagens[ultimoFila][i];
    }
    cout << ")" << endl;
    ultimoFila += 1;
    // fila circular...
    if (ultimoFila==MAXFILA) {
      ultimoFila = 0;
    }
  }

  void Network::initializeNetwork(){
    //Conecta com o servidor
    IPaddress ip;
    cout << "Inicializa Network" << endl;
    //Monta estrutra IPaddress
    if(SDLNet_ResolveHost(&ip,ipServidor,porta)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(1);
    }

    //Inicia cliente
    conexao = SDLNet_TCP_Open(&ip);
    if(!conexao) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }

    SDLNet_TCP_AddSocket(socketSet,conexao);
    
    cout << endl;
    cout << "Conectado no servidor " << ipServidor << " na porta " << porta << endl;

    lerComando();

    if (msg[0] == 'A'){
      cout << "Servidor solicitou para aguardar conexao do guest" << endl;
      cout << "Tecle algo para interromper" << endl;

      host = true;
      while(true){
        cout << backspace << animacao[loop] << flush;
        loop++;
        if(loop == 6){
          loop = 0;
        }
        int numReady = SDLNet_CheckSockets(socketSet, 0);
        if (numReady == -1) {
          cout << "Erro : " <<  SDLNet_GetError() << endl;
          // Finalizar
          SDLNet_TCP_Close(conexao);
          SDLNet_TCP_DelSocket(socketSet,conexao);
          exit(5);

        } else if(numReady) {
          lerComando();
          break;
        }
        // Da um tempo para a CPU
        SDL_Delay(100);
      }

    }else if (msg[0] == 'C'){
      cout << "Servidor conectou-me como guest" << endl;
      host = false;
    }

  }

  bool Network::lerTCP(int tamanho, char* buffer){
    #if DEBUG
      cout << ">lerTCP tamanho("<<tamanho<<")"<<endl;
    #endif
    //Le o comando da mensagem
    int tamLido = SDLNet_TCP_Recv(conexao,buffer,tamanho);
    #if DEBUG
      cout << " lerTCP tamLido ("<<tamLido<<")"<<endl;
      cout << " lerTCP lido (";
      for (int i=0;i<tamLido;i++) {
        cout << buffer[i];
      }
      cout << ")" << endl;
    #endif

    if(tamLido < tamanho) {
      // An error may have occured, but sometimes you can just ignore it
      // It may be good to disconnect sock because it is likely invalid now.
      cout << "Erro na leitura: " << SDLNet_GetError() << endl;

      #if DEBUG
        cout << "<lerTCP return (false)"<<endl;
      #endif
      return false;
    }
    #if DEBUG
      cout << "<lerTCP return (true)"<<endl;
    #endif

    return true;  
  }

  bool Network::escreveTCP(int tamanho){

    #if DEBUG
      cout << ">escreveTCP tamanho("<<tamanho<<")"<<endl;
      cout << " escreveTCP msg (";
      for (int i=0;i<tamanho;i++) {
        cout << msg[i];
      }
      cout << ")" << endl;
    #endif
    int tamEscrito = SDLNet_TCP_Send(conexao,msg,tamanho);
    #if DEBUG
      cout << " escreveTCP tamEscrito (" << tamEscrito << ")" << endl;
    #endif
    if (tamEscrito < tamanho) {
      cout << "Erro na escrita: " << SDLNet_GetError() << endl;
      #if DEBUG
        cout << "<escreveTCP return (false)"<<endl;
      #endif
      return false;
    }
    #if DEBUG
      cout << "<escreveTCP return (true)"<<endl;
    #endif
    return true;
  }

   bool Network::escreveTCPString(string buffer){
      strcpy(msg,buffer.c_str());
      return escreveTCP(buffer.size());

  }  
  


  void Network::lerComando(){
    if (lerTCP(1, msg)){
      if(msg[0]=='F'){
        cout << "Servidor solicitou desconexao " << endl;
        SDLNet_TCP_Close(conexao);
        SDLNet_TCP_DelSocket(socketSet,conexao);
        exit(4);
      }
    } else {
      exit(3);
    }
  }

  bool Network::enviaJogoInicial(int nacao, int nivel){

    cout << "Envia Jogo Inicial Nacao (" << nacao << ") Nivel (" << nivel << ")" << endl;


    stringstream sstm;
    sstm << "D0004P" << nacao << "N" << nivel;
    cout << "SSTM " << sstm.str() << endl;

    return escreveTCPString(sstm.str());

  }

  bool Network::recebeJogoInicial(int &nacao, int &nivel){

    cout << "Recebe Jogo Inicial ";
    lerComando();
    if (lerTCP(4,msg+1)) {
      int tamDados = 0;
      for (int i=1;i<5;i++) {
        tamDados = tamDados * 10 + (msg[i] - '0');
      }
      if (lerTCP(tamDados,msg+5)){
        if(msg[5] == 'P'){
          cout << "Nacao " << msg[6] << " NIvel : " << msg[8] << endl;
          nacao = msg[6] - '0';
          nivel = msg[8] - '0';
          return true;
        } 
      }
    }  
    return false;          

  }
