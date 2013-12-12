#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"

using namespace std;

  //Array de sockets para os clientes
  //30 Jogos rodando, ou seja, 60 clientes
  const int maxClients = 30;
  const int host = 0;
  const int guest = 1;
  const int MAXLEN = 4096;

  char msg[MAXLEN];

  TCPsocket clients[maxClients][2];
  SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(maxClients * 2);

  bool lerTCP(TCPsocket tcpsocket, int tamanho, char* buffer){
    //Le o comando da mensagem
    int tamLido = SDLNet_TCP_Recv(tcpsocket,buffer,tamanho);
    if(tamLido < tamanho) {
      // An error may have occured, but sometimes you can just ignore it
      // It may be good to disconnect sock because it is likely invalid now.
      cout << "Erro na leitura: " << SDLNet_GetError() << endl;
      return false;
    }

    return true;  
  }

  bool escreveTCP(TCPsocket tcpsocket, int tamanho, char* buffer){
    int tamEscrito = SDLNet_TCP_Send(tcpsocket,buffer,tamanho);
    if (tamEscrito < tamanho) {
       cout << "Erro na escrita: " << SDLNet_GetError() << endl;
       return false;
    }
    return true;
  }

  void finaliza(int posicao, int origem, int destino){
    SDLNet_TCP_Close(clients[posicao][origem]);
    SDLNet_TCP_DelSocket(socketSet,clients[posicao][origem]);
    clients[posicao][origem] = NULL;
    // Finaliza destino
    SDLNet_TCP_Send(clients[posicao][destino],(void *) "F", 1);
    SDLNet_TCP_Close(clients[posicao][destino]);
    SDLNet_TCP_DelSocket(socketSet,clients[posicao][destino]);
    clients[posicao][destino] = NULL;
  }


  void trataSocket(int posicao, int origem, int destino){
    bool ok = false;
    cout << "trataSocket Posicao (" << posicao << ") Origem (" <<origem << ") Destino ( "<< destino << ")" << endl;
    // Le o comando da mensagem
    if (lerTCP(clients[posicao][origem],1,msg)){
      if (msg[0] == 'F'){
        cout << "Origem finalizou" << endl;
        finaliza(posicao,origem,destino);
        ok = true;
      } else if (msg[0] == 'D') {
        cout << "Origem enviando dados" << endl;
        //Ver tamanho da mensagem
        if (lerTCP(clients[posicao][origem],4,msg+1)) {
          int tamDados = 0;
          for (int i=1;i<5;i++) {
            tamDados = tamDados * 10 + ( msg[i] - '0' );
          }
          cout << "Tamanho da mensagem " << tamDados << endl;
          if (lerTCP(clients[posicao][origem],tamDados,msg+5)) {
            ok = true;
            // Envia para guest
            if (!escreveTCP(clients[posicao][destino],tamDados+5,msg)) {
              finaliza(posicao,destino,origem);
            }
          }
        }
      } else if (msg[0] == 10 || msg[0] == 13) {
        ok = true;  // despreza o carriage return e o line feed
      } else {
        // Qualquer outra coisa, finaliza as duas conexões
        cout << "Comando (" << msg[0] << ") (" << (int)msg[0] << ") invalido" << endl;
      }
    }
    if (!ok){
      finaliza(posicao,origem,destino);
    }
  }

  int main(){
       // create a listening TCP socket on port 9999 (server)
    IPaddress ip, *ipClient;
    TCPsocket tcpsock,client;
    int flipflop = 0;
    //Inicializa vetor
    for(int i = 0; i<maxClients; i++){
      for(int j = 0; j < 2; j++){
        clients[i][j] = NULL;
      }
    }

    //Monta estrutra IPaddress
    if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(1);
    }

    //Inicia listener
    tcpsock=SDLNet_TCP_Open(&ip);
    if(!tcpsock) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(2);
    }

      cout << endl;
      cout << "Servidor Escutando na porta 9999!" << endl;
      
    while(true){
      // Verifica teclado
      // Descobrir funçao que lê teclado.

      //Espera conexão
      flipflop = !flipflop;
      cout << "Aguardando conexão! (" << flipflop << ")" << endl;
      client = SDLNet_TCP_Accept(tcpsock); 
      if(client != NULL) {  // Novo client conectou
          cout << "Conexão Iniciada!" << endl;
          //Recupera ip do client
          if ((ipClient = SDLNet_TCP_GetPeerAddress(client))) {
            cout << "Cliente conectado: " << SDLNet_Read32(&ipClient->host) << " " << SDLNet_Read16(&ipClient->port) << endl;
            // Verifica se existe slots disponivel
            bool achou = false;
            for(int i = 0; i<maxClients; i++){
                if(clients[i][host] == NULL) {
                   // Manda mensagem de aguardando parceiro
                  cout << "Aguarde conexao do guest" << endl;
                  if(SDLNet_TCP_Send(client,(void *) "A", 1) == 0){
                    cout << "Erro no envio de mensagem" << endl;
                    //Disconecta
                    SDLNet_TCP_Close(client);
                  }else{
                     //Primeiro do par
                    clients[i][host] = client;
                    achou = true;
                    SDLNet_TCP_AddSocket(socketSet,client);
                  }
                  break;
                }
                if(clients[i][guest] == NULL) {
                   // Manda mensagem de parceiro conectado
                  cout << "Guest conectado" << endl;
                  if(SDLNet_TCP_Send(clients[i][host], (void *) "C", 1) == 0){
                    cout << "Host desconetado" << endl;
                    //Disconecta
                    SDLNet_TCP_Close(clients[i][host]);
                    SDLNet_TCP_DelSocket(socketSet,clients[i][host]);
                    // Faz este o primeiro do par
                    cout << "Convertendo para host" << endl;
                    if(SDLNet_TCP_Send(client,(void *) "A", 1) == 0){
                      cout << "Erro no envio de mensagem" << endl;
                      //Disconecta
                      SDLNet_TCP_Close(client);
                    }else{
                      //Host
                      clients[i][host] = client;
                      achou = true;
                      SDLNet_TCP_AddSocket(socketSet,client);
                    }

                  }else{
                    if(SDLNet_TCP_Send(client, (void *) "C", 1) == 0){
                      cout << "Erro no envio de mensagem" << endl;
                    }else{
                      //Guest
                      clients[i][guest] = client;
                      achou = true;
                      SDLNet_TCP_AddSocket(socketSet,client);
                    }
                  }
                  break;
              }
            }
            if(achou == false){
              //Nenhum slot disponivel
              SDLNet_TCP_Send(client,(void *) "F", 1);
              SDLNet_TCP_Close(client);
            }
          }else{
            cout << "Erro na CONEXAO: " << SDLNet_GetError() << endl;
          }
      }
  
      // Verifica se tem mensagem para receber/enviar
      cout << "Verificando mensagem!" << endl;
      int numReady = SDLNet_CheckSockets(socketSet, 0);
      if (numReady == -1) {
          cout << "Erro : " <<  SDLNet_GetError() << endl;
          // Finalizar todo mundo...
      } else if(numReady) {
        // Verifica todos os sockets
        for (int i=0 ;i<maxClients;i++){
          if ((clients[i][host] != NULL ) && (clients[i][guest] != NULL)) {
            cout << "verificando posicao (" << i << ") host";
            if (SDLNet_SocketReady(clients[i][host])) {
              trataSocket(i,host,guest);
            }
            cout << " guest" << endl;
            if(SDLNet_SocketReady(clients[i][guest])) {
              trataSocket(i,guest,host);
            }
          }
        }
      } 
      SDL_Delay(1000);
    }
  }

