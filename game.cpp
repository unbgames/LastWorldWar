#include "game.h"
#include "globalsGame.h" 
#include "Nacao.h"
#include "Unidade.h"
#include "Territorio.h"
#include "SDL/SDL_ttf.h"
#include "Network.h"
#include <list>

#define AVIAO 0
#define NAVIO 1
#define SOLDADO 2
#define CANHAO 3

int height = 0;
int width = 0;

int nacaoHost;
int nivelHost;

// Nacao* nacao1 = new Nacao(400,400,400,400,"Estados Unidos");
// Nacao* nacao2 = new Nacao(400,400,400,400, "Siria");
// Nacao* nacaoSelecionada = nacao1;

// Nacao* nacao1 = NULL;
// Nacao* nacao2 = NULL;
list<Nacao*> nacoes;
list<Territorio*> territorios;

//Nacao* nacaoSelecionada = NULL;
//Nacao* nacaoInimigo = NULL;
Nacao* turno = NULL;

//Territorio* territorioSelecionado = NULL;

//Network* conexaoCliente = new Network();
//Unidade* unidadeSelecionada = NULL;
Unidade* unidadeAlvo = NULL;

int tempo;
int tempoTurno;

int atualizacaoQuadroAnimacao = 1000/10;	//10 vezes por segundo

int sound()
{


	return 1;	
}

bool confereGameOver()
{
	int qtd_territorios = 0, qtd_totalTerritorios = 0;

	for(list<Territorio *>::iterator it = territorios.begin(); it != territorios.end(); it++, qtd_territorios++)
	{
		if( (*(*it)).nacao == nacaoSelecionada )
			qtd_totalTerritorios++;
	}

	if( nivelHost == 1 && qtd_territorios==qtd_totalTerritorios )		//&& nivel == 1 (nivel onde se deve conquistar todos os territorios por exemplo)
		return true;
	else if (nivelHost == 2 && qtd_territorios > qtd_totalTerritorios / 2)
		return true;

	return false;

}

//Funcao Menu
void selecionarMenu(){

	if(event.type == SDL_MOUSEBUTTONUP) 
	{
			
		int X = event.button.x;
		int Y = event.button.y;

		int tileX = X/30;
		int tileY = Y/30;

	
		//Abrir jogo
		if( (tileX>=10 && tileX<=19) && (tileY>=10 && tileY<=13) ){
			/*(*conexaoCliente).initializeNetwork();
			if((*conexaoCliente).host){
				//Colocar mensagem para aguardar conexão do próximo jogador!!!
				cout << "Conectou como host ----> TELA PREPARACAOJOGO" << endl;*/
				scenarioAtual=PREPARACAOJOGO;
				(*audioHandler).playEscolhaNacao();	
			/*}else{
				cout << "Conectou como GUEST ----> TELA LOADING" << endl;
				scenarioAtual=LOADING;	
			}*/
			

		}
		
		//Instrucoes
		if( (tileX>=10 && tileX<=19) && (tileY>=14 && tileY<=17) ){
			
			scenarioAtual=INSTRUCOES;	

		}
		//opcoes
		if( (tileX>=10 && tileX<=19) && (tileY>=18 && tileY<=20) ){
			
			scenarioAtual=OPCOES;
			(*audioHandler).playMusicOpcoes();	

		}

		//Sair	
		if( (tileX>=10 && tileX<=19) && (tileY>=21 && tileY<=24) ) 
		{			
			quit = true;
	
		}


		//creditos
		if( (tileX>=10 && tileX<=19) && (tileY>=25 && tileY<=27) ){
			
			scenarioAtual=CREDITOS;	
			(*audioHandler).playMusicCreditos();
		}

	}
}

void selecionaNacao(){


if(event.type == SDL_MOUSEBUTTONUP) 
	
	{
			
		int X = event.button.x;
		int Y = event.button.y;

		int tileX = X/30;
		int tileY = Y/30;

	
		//EUA
		if( (tileX>=6 && tileX<=15) && (tileY>=12 && tileY<=14) ){
			//Escolheu EUA... Definir como fazer essa definicao
			nacaoHost = 0;
			scenarioAtual=NIVEL;
		}
			
		//Siria	
		if( (tileX>=26 && tileX<=35) && (tileY>=12 && tileY<=14) ) {
			//Escolheu sIRIA... Definir como fazer essa definicao
			nacaoHost = 1;
			scenarioAtual=NIVEL;		
	
		}

		//Voltar
		if( (tileX>=1 && tileX<=10) && (tileY>=20 && tileY<=22) ) {
		
			scenarioAtual=MENU_INICIAL;
	
		}
	}

}



void selecionarNivel(){

	if(event.type == SDL_MOUSEBUTTONUP) 
		{
				
			int X = event.button.x;
			int Y = event.button.y;

			int tileX = X/30;
			int tileY = Y/30;

		
			//Nivel 1
			if( (tileX>=15 && tileX<=24) && (tileY>=8 && tileY<=11) ){
				//Escolheu Nivel 1... Definir como fazer essa definicao
				nivelHost = 1;
				scenarioAtual=LOADING;
			}
				
			//Nivel 2
			if( (tileX>=15 && tileX<=24) && (tileY>=12 && tileY<=14) ) {
				//Escolheu NIvel 2... Definir como fazer essa definicao
				nivelHost = 2;
				scenarioAtual=LOADING;		
		
			}

			//Nivel 3
			if( (tileX>=15 && tileX<=24) && (tileY>=15 && tileY<=18) ) {
			//Escolheu NIvel 3... Definir como fazer essa definicao
				nivelHost = 3;
				scenarioAtual=LOADING;
		
			}

			//Nivel 4
			if( (tileX>=15 && tileX<=24) && (tileY>=19 && tileY<=22) ) {
			//Escolheu NIvel 4... Definir como fazer essa definicao
				nivelHost = 4;
				scenarioAtual=LOADING;
		
			}
			
			//Nivel 5
			if( (tileX>=15 && tileX<=24) && (tileY>=23 && tileY<=25) ) {
			//Escolheu NIvel 5... Definir como fazer essa definicao
				nivelHost = 5;
				scenarioAtual=LOADING;
		
			}

			//Voltar
			if( (tileX>=1 && tileX<=10) && (tileY>=24 && tileY<=26) ) {
			
				scenarioAtual=MENU_INICIAL;
		
			}
			
			

		}
}

void selecionarOpcoes(){
	if(event.type == SDL_MOUSEBUTTONUP) 
		{
				
			int X = event.button.x;
			int Y = event.button.y;

			int tileX = X/30;
			int tileY = Y/30;

		
			//Aumentar SoundTrack
			if( (tileX>=15 && tileX<=24) && (tileY>=8 && tileY<=11) ){
				//Escolheu Nivel 1... Definir como fazer essa definicao
			
				printf("AUmentar Sound Track\n");
			}
				
			//Diminuir SoundTrack
			if( (tileX>=15 && tileX<=24) && (tileY>=12 && tileY<=14) ) {
				//Escolheu NIvel 2... Definir como fazer essa definicao
			
				printf("DIminuir SoundTrACK\n");	
		
			}

			//Aumentar Sound Effect
			if( (tileX>=15 && tileX<=24) && (tileY>=15 && tileY<=18) ) {
			//Escolheu NIvel 2... Definir como fazer essa definicao
				printf("aUMENTAR SoundEFFECT\n");	
		
			}

			//Diminuir Sound Effect
			if( (tileX>=15 && tileX<=24) && (tileY>=19 && tileY<=22) ) {
			//Escolheu NIvel 3... Definir como fazer essa definicao
					printf("DIminuir SoundEFFECT\n");	
		
			}

			//Voltar
			if( (tileX>=1 && tileX<=10) && (tileY>=24 && tileY<=26) ) {
			
				scenarioAtual=MENU_INICIAL;
				(*audioHandler).playMusic();		
			}
			
			

		}
}

void mudarTurno()
{
	territorioSelecionado = NULL;
	if( unidadeSelecionada != NULL )
	{
		(*unidadeSelecionada).selecionado = false;
		unidadeSelecionada = NULL;
	}

	/*
	if( turno == nacoes.back() )
		turno = nacoes.front();
	else
		turno = nacoes.back();
	*/

	if( nacaoSelecionada == nacoes.front() )
		nacaoSelecionada = nacoes.back();
	else
		nacaoSelecionada = nacoes.front();

	(*nacaoSelecionada).coletar();

	for(list<Unidade *>::iterator it1 = (*nacoes.front()).exercito.begin(); it1 != (*nacoes.front()).exercito.end(); it1++)
			(*(*it1)).qtdMovimentos = (*(*(*it1)).tipo).qtdMovimentos; 	
}

//main loop functions
int initialize()
{
	/*	Setando coisas	*/

    quit = false;

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		cout << "Problemas ao inicializar sistemas e subsistemas do SDL" << endl;    
		return -1;
	}

    //Initialize SDL_ttf 
    if( TTF_Init() == -1 ) 
	    return false;

	//The attributes of the screen
	const int SCREEN_WIDTH = 1980;
	const int SCREEN_HEIGHT = 1024 ;
	const int SCREEN_BPP = 32;

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
		cout << "Problemas inicializando o video" << endl;
        return -2;
    }

    //Set the window caption
    SDL_WM_SetCaption( "The World Last War", NULL );	

	//objetos principais
	ImageHandlerSDLObj = new ImageHandlerSDL();
	drawObj = new Draw();
	randomObj = new Random();
	timer = new Timer();
	audioHandler = new AudioHandler();
	fontHandler = new FontHandler();

    //Load the images
	logoEmpresa = (*ImageHandlerSDLObj).load_image("images/gamaSoft.jpg",0);
  logoJogo = (*ImageHandlerSDLObj).load_image("images/logo.png",0);
	logoRecursos = (*ImageHandlerSDLObj).load_image("images/recursosTecnologicos.png",0);
	civilizationUnits = (*ImageHandlerSDLObj).load_image("images/unidades2.png",0);
	classificacaoIndicativa = (*ImageHandlerSDLObj).load_image("images/classificacaoIndicativa.png",0);	
	menu = (*ImageHandlerSDLObj).load_image("images/menu.png",0);
	mapa = (*ImageHandlerSDLObj).load_image("images/gamasoft_mapaTeste.png",0);
	escolhaNacao = (*ImageHandlerSDLObj).load_image("images/telaNacao.png", 0);
	nivel = (*ImageHandlerSDLObj).load_image("images/telaNivel.png", 0);
  telaInstrucoes = (*ImageHandlerSDLObj).load_image("images/telaInstrucoes.png", 0);
  telaOpcoes = (*ImageHandlerSDLObj).load_image("images/telaOpcoes.png", 0);
  telaCreditos = (*ImageHandlerSDLObj).load_image("images/telaCreditos.png", 0);
  telaLoading = (*ImageHandlerSDLObj).load_image("images/telaLoading.png", 0);
  loading = (*ImageHandlerSDLObj).load_image("images/loadingPiece.png", 0);

	//quadradoTransparente para sobrepor tiles destacando-os
	transparentSurface = (*drawObj).MyFillRect( 30, 30, screen, 100);
	
	(*audioHandler).initialize();
	(*fontHandler).initialize();

	(*audioHandler).playMusic();
	// (*timer).start();

	soldado = new ClasseUnidade("Soldado", 4, 7, TERRESTRE, 50, 50, 0, 0, 2);
	canhao = new ClasseUnidade("Canhao", 3, 10, TERRESTRE, 200, 50, 100, 0, 3);
	navio = new ClasseUnidade("Navio", 6, 13, AQUATICO, 100, 50, 100, 100, 4);
	aviao = new ClasseUnidade("Aviao", 9, 20, QUALQUER_AMBIENTE, 100, 100, 100, 100, 6);

	return 1;	//sucess
}

int finalize()
{
    //Free the surfaces
    SDL_FreeSurface( logoEmpresa );
    SDL_FreeSurface( logoJogo );
    SDL_FreeSurface(logoRecursos );
    SDL_FreeSurface( menu );
    SDL_FreeSurface( classificacaoIndicativa );
    SDL_FreeSurface( mapa );
    SDL_FreeSurface( escolhaNacao );
    SDL_FreeSurface( nivel );
    SDL_FreeSurface( telaInstrucoes );
    SDL_FreeSurface( telaOpcoes );
    SDL_FreeSurface( telaCreditos );
    SDL_FreeSurface( telaLoading );
    SDL_FreeSurface( loading );

    SDL_FreeSurface( messageRecursos );	
    SDL_FreeSurface( messageUnidades );	
    SDL_FreeSurface( messageTerritorios );
    SDL_FreeSurface( messageGameOver );

		SDL_FreeSurface( opcaoJogar );	
		SDL_FreeSurface( opcaoInstrucoes );	
		SDL_FreeSurface( opcaoOpcoes );	
		SDL_FreeSurface( opcaoSair );	
    SDL_FreeSurface( opcaoCreditos );	
    SDL_FreeSurface( textoCompleto );
    SDL_FreeSurface( creditosCompleto );
    SDL_FreeSurface( textoAudio );
    SDL_FreeSurface( textoSoundT );
    SDL_FreeSurface( textoSoundE );    

    SDL_FreeSurface( timeEua );	
		SDL_FreeSurface( timeSiria );	
    SDL_FreeSurface( opcaoVoltar );

    SDL_FreeSurface( opcaoNivel1 );
    SDL_FreeSurface( opcaoNivel2 );
    SDL_FreeSurface( opcaoNivel3 );
    SDL_FreeSurface( opcaoNivel4 );
    SDL_FreeSurface( opcaoNivel5 );

	SDL_FreeSurface( transparentSurface );

	//cenario
	if(scenarioAtual==INICIO)
		finalizeCenario1();

	//delete other objects
	delete(ImageHandlerSDLObj);
	delete(drawObj);
	delete(randomObj);

	(*audioHandler).finalize();
	(*fontHandler).finalize();

	delete(soldado);
	delete(canhao);
	delete(navio);
	delete(aviao);

    //Quit SDL
    SDL_Quit();

	return 1;
}

void carregarLoading(){

	int recursos = 0;
	/*if ((*conexaoCliente).host){
		(*conexaoCliente).enviaJogoInicial(nacaoHost, nivelHost);

	} else{
		(*conexaoCliente).recebeJogoInicial(nacaoHost, nivelHost);
	}*/

	if(nivelHost == 1){
		recursos = 3000;
	}else if(nivelHost == 2){
		recursos = 50;
	}else {
		recursos = 400;
	}

	nacoes.push_back(new Nacao(recursos,recursos,recursos,recursos,"Estados Unidos",0x0000FF));
	nacoes.push_back(new Nacao(recursos,recursos,recursos,recursos,"Siria",0x00FF00));

	/*if((*conexaoCliente).host){
		if(nacaoHost == 0){
				// nacaoSelecionada = nacao1;
				// nacaoInimigo = nacao2;
				nacaoSelecionada = nacoes.front();
				nacaoInimigo = nacoes.back();
				meuTurno = true;
		}else{
			nacaoSelecionada = nacoes.back();
			nacaoInimigo = nacoes.front();
		}
	}else{
		if(nacaoHost == 0){
				nacaoSelecionada = nacoes.back();
				nacaoInimigo = nacoes.front();
		}else{
			nacaoSelecionada = nacoes.front();
			nacaoInimigo = nacoes.back();
			meuTurno = true;
		}
	}
	nacaoInimigo = nacoes.back();*/
	if(nacaoHost == 0)
		nacaoSelecionada = nacoes.front();
	else
		nacaoSelecionada = nacoes.back();

	meuTurno = true;
	
	int i = 0;
	int x = 300;
	int y = 432;


	SDL_FillRect(screen, NULL, 0x000000);
	(*drawObj).apply_surface( height, width, telaLoading, screen,0);
	
	for(i = 0; i < 13 ; i++)
	{
		//SDL_Delay(400);
		//CRIAR THREAD PARA RODAR ISSO
		//cout << "Valor de i : " << i << endl;
		(*drawObj).apply_surface( x, y, loading, screen,0);

		x+= 30;

		if(i == 12){
			
			break;
		}
	}
			initializeCenario1();
			(*timer).start();
			scenarioAtual=INICIO;	
}


int finalizeCenario1()
{
	(*cenario).finalize();
	delete(cenario);

	while (!territorios.empty())
	{
		delete( territorios.front() );
		territorios.pop_front();
	}

	while (!nacoes.empty())
	{
		(*nacoes.front()).finalize();
		delete( nacoes.front() );
		nacoes.pop_front();
	}

	return 1;
}







//function of game main loop

int	updateTime()
{
	
	return 1;
}

int receiveNetworkMessages()
{
	/*if ((*conexaoCliente).recebeJogada(nacaoInimigo)) {
			return 1;	
	}*/
	return 0;
}

void selecionarUnidadeNacao(Nacao* nacao, int tileX, int tileY)
{
		if( (*cenario).tiles[tileY][tileX] == NULL )
			return;

		if( (*(*cenario).tiles[tileY][tileX]).ocupante != NULL && 
			(*(*(*cenario).tiles[tileY][tileX]).ocupante).nacao == nacao )
		{
			if(unidadeSelecionada==0)
			{
				unidadeSelecionada = (*(*cenario).tiles[tileY][tileX]).ocupante;
				
				if ( (*unidadeSelecionada).isDead == false )
				{
					(*unidadeSelecionada).selecionado = true;
					(*audioHandler).playEffect();	
				}			
			}					
			else
			{
				if( unidadeSelecionada == (*(*cenario).tiles[tileY][tileX]).ocupante )
				{
					(*unidadeSelecionada).selecionado = false;
					
					if( (*unidadeSelecionada).unidadesGuardadas.size() > 0 )
					{	
						unidadeSelecionada = (*unidadeSelecionada).unidadesGuardadas.front();						
						(*unidadeSelecionada).selecionado = true;
					}
					else
						unidadeSelecionada = NULL;
				}
				else if( unidadeSelecionada == (*(*(*cenario).tiles[tileY][tileX]).ocupante).unidadesGuardadas.front() )
				{
					(*unidadeSelecionada).selecionado = false;
					unidadeSelecionada = NULL;
				}
				/*(*unidadeSelecionada).selecionado = false;					
				unidadeAlvo = (*it1);
				(*unidadeSelecionada).attack(unidadeAlvo);
				(*audioHandler).playEffect_Enemy();
				unidadeSelecionada = 0;					
				unidadeAlvo = 0;	*/
			}
		}
}

void mostrandoUnidadesNacao(Nacao nacao)
{
	//Laço responsável por criar (show) todas as unidades criadas na Nacao
	for(list<Unidade *>::iterator it1 = nacao.exercito.begin(); it1 != nacao.exercito.end(); it1++)
	{
		if((*it1) != NULL && !(*(*it1)).isDead)
		(*(*it1)).show(); 
	}
}
		
int get_inputs()
{
	
    while( SDL_PollEvent( &event ) )
    {
    	if( event.type == SDL_QUIT )	//If the user has Xed out the window
    	{
        quit = true;
   		}
			if( event.type == SDL_KEYDOWN )
			{
				if( event.key.keysym.sym == SDLK_ESCAPE ) 
					quit = true;
		
				/*
				//Remover última unidade adicionada na lista: Vai ser útil quando implementarmos o ataque corretamente
				if(event.key.keysym.sym == SDLK_3 && unidadeSelecionada != 0)
					(*unidadeSelecionada).isDead = true;
				*/

				if (meuTurno) {

			if(unidadeSelecionada != 0)
			{				
				if( (*unidadeSelecionada).qtdMovimentos > 0 )
				{
					int destX = (*unidadeSelecionada).posX;
					int destY = (*unidadeSelecionada).posY;

					if( event.key.keysym.sym == SDLK_a )
					{
						destX -= 1;
						
					}
					if( event.key.keysym.sym == SDLK_d )
					{
						destX += 1;
						
					}
					if( event.key.keysym.sym == SDLK_w ){
						destY -= 1;
						
					}
					if( event.key.keysym.sym == SDLK_s ){
						destY += 1;
						
					}

					if( ((*unidadeSelecionada).posX == destX) && ((*unidadeSelecionada).posY == destY) )	//se nao tiver escolhido nova posicao
						break;
					if( (destX < 0 || destX >= COLUNAS_MAPA) || (destY < 0 || destY >= LINHAS_MAPA) )			//limites do mapa
						break;

					if( (*unidadeSelecionada).canMove((*cenario).tiles[destY][destX]) )
					{
						if(unidadeSelecionada == NULL)
							continue;

						if( (*(*cenario).tiles[(*unidadeSelecionada).posY][(*unidadeSelecionada).posX]).ocupante == unidadeSelecionada )
							(*(*cenario).tiles[(*unidadeSelecionada).posY][(*unidadeSelecionada).posX]).ocupante = NULL;
						else
						{
							(*(*(*cenario).tiles[(*unidadeSelecionada).posY][(*unidadeSelecionada).posX]).ocupante).unidadesGuardadas.pop_front();
							(*unidadeSelecionada).isDead = false;
							(*(*cenario).tiles[(*unidadeSelecionada).posY][(*unidadeSelecionada).posX]).ocupante = NULL;
						}

							/*if( event.key.keysym.sym == SDLK_a )
							{
								(*conexaoCliente).pushMovimento((*unidadeSelecionada).posX,(*unidadeSelecionada).posY,'a');
							}
							if( event.key.keysym.sym == SDLK_d )
							{
								(*conexaoCliente).pushMovimento((*unidadeSelecionada).posX,(*unidadeSelecionada).posY,'d');
							}
							if( event.key.keysym.sym == SDLK_w ){
								(*conexaoCliente).pushMovimento((*unidadeSelecionada).posX,(*unidadeSelecionada).posY,'w');
							}
							if( event.key.keysym.sym == SDLK_s ){
								(*conexaoCliente).pushMovimento((*unidadeSelecionada).posX,(*unidadeSelecionada).posY,'s');
							}*/
							
							(*unidadeSelecionada).posX = destX;
							(*unidadeSelecionada).posY = destY;

							if( (*unidadeSelecionada).unidadesGuardadas.size() > 0 )
							{
								for(list<Unidade*>::iterator it = (*unidadeSelecionada).unidadesGuardadas.begin(); it != (*unidadeSelecionada).unidadesGuardadas.end(); it++)
								{
									(*(*it)).posX = destX;
									(*(*it)).posY = destY;
								}
							}

							(*(*cenario).tiles[destY][destX]).ocupante = unidadeSelecionada;
							(*unidadeSelecionada).qtdMovimentos--;

							if( (*(*cenario).tiles[destY][destX]).territorio != NULL)
							{
								if(		(*(*(*cenario).tiles[destY][destX]).territorio).tiles.front() == (*cenario).tiles[destY][destX] &&
										(*unidadeSelecionada).nacao != (*(*(*cenario).tiles[destY][destX]).territorio).nacao )
									(*(*(*cenario).tiles[destY][destX]).territorio).serConquistado((*unidadeSelecionada).nacao);
							}
					}
					else if( (*unidadeSelecionada).isDead )
					{
						(*(*cenario).tiles[(*unidadeSelecionada).posY][(*unidadeSelecionada).posX]).ocupante = NULL;
						unidadeSelecionada = NULL;
					}
				}
			}

			
			if(event.key.keysym.sym == SDLK_t)
			{
				mudarTurno();
			}
			

			//alternando modo do mapa
			if(event.key.keysym.sym == SDLK_0)
			{
				modo++;
				modo = modo % 4;		//4 modos
			}
			
			/*int posXBase = (*(*(*nacaoSelecionada).territorios.front()).tiles.front()).posX;
			int posYBase = (*(*(*nacaoSelecionada).territorios.front()).tiles.front()).posY;*/
			
			if( territorioSelecionado != NULL && (*territorioSelecionado).nacao == nacaoSelecionada )
			{
				if(event.key.keysym.sym == SDLK_1)
					(*territorioSelecionado).criarUnidade(soldado);

				if(event.key.keysym.sym == SDLK_2)
					(*territorioSelecionado).criarUnidade(canhao);

				if(event.key.keysym.sym == SDLK_3)
				{
					//Base Marinha sendo o segundo tile do territorio ou ver uma posicao a direita/esquerda que seja agua
					(*territorioSelecionado).criarUnidade(navio);
				}

				if(event.key.keysym.sym == SDLK_4)
					(*territorioSelecionado).criarUnidade(aviao);			
			}					
	}			
}
		
			// Eventos de mouse
			if(event.type == SDL_MOUSEBUTTONUP && meuTurno)
			{
				int X = event.button.x;
				int Y = event.button.y;

				int tileX = X/30;
				int tileY = Y/30;

				if( event.button.button == SDL_BUTTON_RIGHT )
				{
					if ( (*(*cenario).tiles[tileY][tileX]).territorio != NULL &&
					(*cenario).tiles[tileY][tileX] == (*(*(*cenario).tiles[tileY][tileX]).territorio).tiles.front() )
					{
						territorioSelecionado = (*(*cenario).tiles[tileY][tileX]).territorio;
						return 1;
					}
					territorioSelecionado = NULL;
				}

				//unidadeSelecionada
				if( scenarioAtual==INICIO && (nacaoSelecionada != 0 || unidadeSelecionada != 0) )
					selecionarUnidadeNacao(nacaoSelecionada, tileX, tileY);
			}
		
    }

	return 1;
}

int tratarColisoes()
{
	
	return 1;
}

int atualizarEstados()
{
	quadroEstado++;
	if(scenarioAtual==TELA_INICIAL)
	{
		switch(quadroEstado)
		{
			case 2:
					SDL_FillRect(screen, NULL, 0xFFFFFF);
					(*drawObj).apply_surface( height + 200,  width + 100, logoEmpresa, screen,0);
					SDL_Delay(2000);
					break;

			case 3:
					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height + 200,width, logoRecursos, screen,0);
					SDL_Delay(2000);			
					break;
			case 4:
					SDL_FillRect(screen, NULL, 0xFFFFFF);
					(*drawObj).apply_surface( height, width, classificacaoIndicativa, screen,0);
					SDL_Delay(2000);
					break;
					
			case 6:
					SDL_FillRect(screen, NULL, 0xFFFFFF);
					(*drawObj).apply_surface( height,width, menu, screen,0);
					SDL_Delay(2000);				//trabalhando com esse para esta entrega
					break;


			
		}
	}		

	return 1;
}

int do_logic()
{	
	tratarColisoes();
	atualizarEstados();

	return 1;
}



int do_drawing()
{
	if(scenarioAtual!=INICIO)
		carregarLoading();
	//comecando do inicio do jogo
	scenarioAtual=INICIO;
	//Telas de apresentacao

	if(scenarioAtual==TELA_INICIAL)
	{
		switch(quadroEstado)			//switch para diferenciar parte da animacao por quadro
		{
			case 1:
					SDL_FillRect(screen, NULL, 0xFFFFFF);
					(*drawObj).apply_surface( height, width, logoEmpresa, screen,0);
					break;

			case 2:
					SDL_FillRect(screen, NULL, 0xFFFFFF);
					(*drawObj).apply_surface( height + 50, width , logoRecursos, screen,0);
					break;
			
			case 3:
					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height , width, classificacaoIndicativa, screen,0);
					break;

			case 4:
			default:
					scenarioAtual = MENU_INICIAL;					
					(*audioHandler).playVoiceMenu();
					break;
		}
	}


	//Menu Principal!!
	if(scenarioAtual==MENU_INICIAL){

					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height, width, menu, screen,0);
					

					SDL_Color textColor = {0, 0, 0, 0};
					sprintf(jogar,"Jogar");
					sprintf(instrucoes,"Instruções");
					sprintf(opcoes,"Opções");
					sprintf(sair,"Sair");
					sprintf(creditos,"Créditos");
	
				opcaoJogar = TTF_RenderText_Solid( (*fontHandler).fontMenu, jogar,textColor );
					opcaoInstrucoes = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, instrucoes,textColor );
					opcaoOpcoes = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, opcoes,textColor );
					opcaoSair = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, sair,textColor );
					opcaoCreditos = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, creditos,textColor );

					(*drawObj).apply_surface( height + 400, width + 330, opcaoJogar, screen, 0 );
					(*drawObj).apply_surface( height + 330, width + 440, opcaoInstrucoes, screen, 0 );
					(*drawObj).apply_surface( height + 380, width + 550, opcaoOpcoes, screen, 0 );
					(*drawObj).apply_surface( height + 400, width + 660, opcaoSair, screen, 0 );
					(*drawObj).apply_surface( height + 350, width + 770, opcaoCreditos, screen, 0 );

					
					selecionarMenu();
					
	}
  //Telas Instrucoes
	if (scenarioAtual==INSTRUCOES){

					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( 0, 0, telaInstrucoes, screen,0);
					

					//SDL_Color textColor = {0, 0, 0, 0};
					SDL_Color textColor = {255, 255, 255, 255};
					sprintf(instrucoes,"Instruções");
					sprintf(texto,"Escrever o jeito de jogar, com os diferentes de níveis.");
					sprintf(voltar,"Voltar");
					
					opcaoInstrucoes = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, instrucoes,textColor );
					textoCompleto = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, texto,textColor );
					opcaoVoltar = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, voltar,textColor );

					(*drawObj).apply_surface( height +  520, width +  290, opcaoInstrucoes, screen, 0 );
					(*drawObj).apply_surface( height +  520, width +  390, textoCompleto, screen, 0 );
					(*drawObj).apply_surface( height +  100, width +  630, opcaoVoltar, screen, 0 );
					//COlocar opcao de voltarp ara o menu principal
	}
	//Telas Opcoes
	if (scenarioAtual==OPCOES){

					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height, width, telaOpcoes, screen,0);
					

					//SDL_Color textColor = {0, 0, 0, 0};
					SDL_Color textColor = {255, 255, 255, 255};
					sprintf(audio,"Áudio");
					sprintf(soundT,"SoundTrack");
					sprintf(soundE,"Sound Effects");
					sprintf(voltar,"Voltar");

					textoAudio = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, audio,textColor );
					textoSoundT = TTF_RenderUTF8_Solid( (*fontHandler).font, soundT,textColor );
					textoSoundE = TTF_RenderUTF8_Solid( (*fontHandler).font, soundE,textColor );
					opcaoVoltar = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, voltar,textColor );

					(*drawObj).apply_surface( height +  520, width +  250, textoAudio, screen, 0 );
					(*drawObj).apply_surface( height +  300, width +  350, textoSoundT, screen, 0 );
					(*drawObj).apply_surface( height +  300, width +  450, textoSoundE, screen, 0 );
					(*drawObj).apply_surface( height +  100, width +  750, opcaoVoltar, screen, 0 );
					//COlocar opcao de voltarp ara o menu principal

					selecionarOpcoes();

	}

	if(scenarioAtual==CREDITOS){

					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height, width, telaCreditos, screen,0);
					

					SDL_Color textColor = {255, 255, 255, 255};
					sprintf(creditosTexto,"Programadores: Fernando Paixão, Gabriela Navarro, Matheus Tristão Artistas: Gabriela Navarro e Victor Navarro");
					sprintf(voltar,"Voltar");
	
					creditosCompleto = TTF_RenderUTF8_Solid( (*fontHandler).font, creditosTexto,textColor );
					opcaoVoltar = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, voltar,textColor );

					(*drawObj).apply_surface( height +  400, width +  330, creditosCompleto, screen, 0 );


					if(event.type == SDL_MOUSEBUTTONUP) 
						
						{
								
							int X = event.button.x;
							int Y = event.button.y;

							int tileX = X/30;
							int tileY = Y/30;

							//Voltar
							if( (tileX>=1 && tileX<=10) && (tileY>=20 && tileY<=22) ) {
							
								scenarioAtual=MENU_INICIAL;
						
							}
						}
					
	}

	//Ecolha da nacao
	if(scenarioAtual==PREPARACAOJOGO)
	{

		SDL_FillRect(screen, NULL, 0x000000);
		(*drawObj).apply_surface( height, width, escolhaNacao, screen,0);

			SDL_Color textColor = {0, 0, 0, 0};
			sprintf(eua,"EUA");
			sprintf(siria,"Síria");
			sprintf(voltar,"Voltar");
			

					timeEua = TTF_RenderText_Solid( (*fontHandler).fontMenu, eua,textColor );
			timeSiria = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, siria,textColor );
			opcaoVoltar = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, voltar,textColor );
			
			(*drawObj).apply_surface( height +  310, width +  390, timeEua, screen, 0 );
			(*drawObj).apply_surface( height +  900, width +  380, timeSiria, screen, 0 );
			(*drawObj).apply_surface( height +  100, width +  630, opcaoVoltar, screen, 0 );

			selecionaNacao();
	}

	//Escolha do nivel
	if (scenarioAtual==NIVEL){

					SDL_FillRect(screen, NULL, 0x000000);
					(*drawObj).apply_surface( height, width, nivel, screen,0);
					

					SDL_Color textColor = {0, 0, 0, 0};

					sprintf(nivel1,"Nível 1");
					sprintf(nivel2,"Nível 2");
					sprintf(nivel3,"Nível 3");
					sprintf(nivel4,"Nível 4");
					sprintf(nivel5,"Nível 5");
					sprintf(voltar,"Voltar");
	
					opcaoNivel1 = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, nivel1,textColor );
					opcaoNivel2 = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, nivel2,textColor );
					opcaoNivel3 = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, nivel3,textColor );
					opcaoNivel4 = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, nivel4,textColor );
					opcaoNivel5 = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, nivel5,textColor );
					opcaoVoltar = TTF_RenderUTF8_Solid( (*fontHandler).fontMenu, voltar,textColor );

					(*drawObj).apply_surface( height +  520, width +  290, opcaoNivel1, screen, 0 );
					(*drawObj).apply_surface( height +  520, width +  390, opcaoNivel2, screen, 0 );
					(*drawObj).apply_surface( height +  520, width +  500, opcaoNivel3, screen, 0 );
					(*drawObj).apply_surface( height +  520, width +  610, opcaoNivel4, screen, 0 );
					(*drawObj).apply_surface( height +  520, width +  720, opcaoNivel5, screen, 0 );
					(*drawObj).apply_surface( height +  80, width +  750, opcaoVoltar, screen, 0 );
					
					selecionarNivel();
	}

	//Telas Loading
	if (scenarioAtual==LOADING){

		carregarLoading();
					
	}
	//Inicio do jogo
	if(scenarioAtual==INICIO)
	{

		cout << "jah entrou" << endl;
		//limpando tela anterior colocando a cor branca no lugar
		SDL_FillRect(screen, NULL, 0xFFFFFF);	

		//desenhando mapa de bits de acordo ao modo
		if(modo == MODO_NORMAL) 
		{
			(*drawObj).apply_surface( height, width, mapa, screen,0);
			for(int i = 0; i < (*cenario).numeroTilesY; i++)
			{
				for(int j = 0; j < (*cenario).numeroTilesX; j++)
				{								
					(*(*cenario).tiles[i][j]).show(false);
				}
			}
		}		
		else
		{
			for(int i = 0; i < (*cenario).numeroTilesY; i++)
			{
				for(int j = 0; j < (*cenario).numeroTilesX; j++)
				{								
					(*(*cenario).tiles[i][j]).show(true);
				}
			}
		}
		



		for(list<Territorio*>::iterator it = territorios.begin(); it != territorios.end(); it++) 
		{
			(*(*it)).mostrarCapital();
		}
		
		for(list<Nacao*>::iterator it = nacoes.begin(); it != nacoes.end(); it++) 
		{
			mostrandoUnidadesNacao(*(*it));
		}
		if(unidadeSelecionada != NULL)
			(*unidadeSelecionada).show();

		(*nacaoSelecionada).carregaScore();

		(*drawObj).apply_surface( height, width + 0*40, messageRecursos, screen, 0 );
		(*drawObj).apply_surface( height, width + 1*40, messageUnidades, screen, 0 );	
		(*drawObj).apply_surface( height, width + 2*40, messageTerritorios, screen, 0 );	

		SDL_Color textColor = {255, 255, 255, 255};
		string auxGeneralInfo = "";
		if( tempo == -1 )
			auxGeneralInfo = "oo";
		else if( tempoTurno != 0 )
			auxGeneralInfo = "para fim do turno";
		else
			auxGeneralInfo = "para fim do jogo";

		sprintf(scoreGeneralInfo,"Tempo Restante %d %s", tempo, auxGeneralInfo.c_str() );
		messageGeneralInfo = TTF_RenderText_Solid( (*fontHandler).font, scoreGeneralInfo, textColor );
		(*drawObj).apply_surface( height+2*260, width + 3*40, messageGeneralInfo, screen, 0 );

		gameOver = confereGameOver();

		if(gameOver)
		{
			SDL_Color textColor = {255, 255, 255, 255};
			sprintf(scoreGameOver,"Game Over %s Ganhou! \\o/", (*nacaoSelecionada).nome.c_str());
			messageGameOver = TTF_RenderText_Solid( (*fontHandler).font, scoreGameOver, textColor );
			(*drawObj).apply_surface( height, width + 4*40, messageGameOver, screen, 0 );
		}
		else if ( territorioSelecionado != NULL )
		{
			string dominante = "Ninguem";

			if( (*territorioSelecionado).nacao != NULL )
				dominante = (*(*territorioSelecionado).nacao).nome;

			SDL_Color textColor = {255, 0, 0, 0};
			sprintf( scoreGameOver,"Territorio %s de %s: Turnos Producao %d", (*territorioSelecionado).nome.c_str(), dominante.c_str(), (*territorioSelecionado).pontosProducao );
			messageGameOver = TTF_RenderText_Solid( (*fontHandler).font, scoreGameOver, textColor );
			(*drawObj).apply_surface( height, width + 3*40, messageGameOver, screen, 0 );
		}
		else if ( unidadeSelecionada != NULL )
		{
			SDL_Color textColor = {255, 0, 0, 0};
			sprintf( scoreGameOver,"Unidade %s: Forca %d Turnos Criacao %d", (*(*unidadeSelecionada).tipo).nome.c_str(), (*(*unidadeSelecionada).tipo).forca, (*(*unidadeSelecionada).tipo).custoTurnos );
			messageGameOver = TTF_RenderText_Solid( (*fontHandler).font, scoreGameOver, textColor );
			(*drawObj).apply_surface( height, width + 3*40, messageGameOver, screen, 0 );
		}
	}
		


	if( SDL_Flip( screen ) == -1 )
	{
		cout << "Nao conseguiu realizar a funcao SDL_Flip" << endl;
	    return -1;
	}

	if(gameOver)
	{
		finalizeCenario1();
		scenarioAtual = MENU_INICIAL;
		SDL_Delay( 5000 );
		cout << "saiu" << endl;
	}

    frame++;
	if( frame % FRAMES_PER_SECOND == 0 && tempo != -1 )
		tempo--;

	//pra animacao
	/*for(list<Nacao *>::iterator it1 = nacoes.begin(); it1 != nacoes.end(); it1++)
	{	
		(*(*it)).atualizaQuadroExercito();
	}*/

	if( tempo <= 0 && tempoTurno != 0 )
	{
		tempo = tempoTurno;
		mudarTurno();
	}
	else
		gameOver = confereGameOver();

    //If a second has passed since the caption was last updated
	if( (*timer).get_ticks() < 1000 / FRAMES_PER_SECOND )
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - (*timer).get_ticks() );
    }

	return 1;
}

//diferentes cenarios
int initializeCenario1()
{
	nivelHost = 1;
	unidadeSelecionada = NULL;
	territorioSelecionado = NULL;

	int auxVez;

	tempo = -1;
	tempoTurno = 0;

	if(nivelHost == 5)
		tempo = -1;
	else if(nivelHost == 4)
	{
		tempoTurno = 2*60;
		tempo = tempoTurno;
	}
	else if(nivelHost == 3)
		tempo = 30*60;
	else
		tempo = -1;


	gameOver = false;
	(*audioHandler).playMusic();

	auxVez = (*randomObj).gerarNumero(2);
	if(auxVez == 1)
		turno = nacoes.front();
	else
		turno = nacoes.back();


	territorios.push_back(new Territorio("EUA"));
	territorios.push_back(new Territorio("Siria"));

	int i = 0;
	for(list<Territorio *>::iterator it = territorios.begin(); i < 2 && it != territorios.end(); it++, i++)
	{
		if(i==0)
			(*(*it)).serConquistado( nacoes.front() );
		if(i==1)
			(*(*it)).serConquistado( nacoes.back() );
	}

	int **mapaMundi = (int**)calloc(LINHAS_MAPA*COLUNAS_MAPA, sizeof(int*));
	for(int i = 0; i<LINHAS_MAPA; i++)
	{
		mapaMundi[i] = (int*)calloc(COLUNAS_MAPA, sizeof(int));
	}

	//criando a variavel auxiliar apenas para aproveitar esta forma de declaracao de array com chaves, carregar de arquivo depois
	int auxMapaMundi[LINHAS_MAPA][COLUNAS_MAPA] = 
			   {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0},
				{0, 0, 1, 1, 1, 3, 1, 2, 1, 0, 5, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
				{0, 0, 1, 1, 1, 3, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
				{0, 0, 1, 1, 6, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
				{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 5, 1, 3, 1, 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 5, 0},
				{0, 0, 0, 0, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 1, 1, 0, 0},
				{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
				{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 2, 1, 1, 0, 0},
				{0, 0, 0, 0, 0, 1, 1, 1, 2, 6, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 6, 1, 0, 0, 0},
				{0, 0, 0, 5, 0, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0, 1, 6, 3, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
				{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 3, 6, 1, 0, 0, 5, 0, 1, 0, 1, 6, 1, 0},
				{0, 0, 0, 0, 0, 1, 6, 1, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 1, 5},
				{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				{0, 0, 0, 0, 5, 0, 1, 1, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 1, 1, 2, 6, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
	for(int i = 0; i<LINHAS_MAPA; i++)
	{
		for(int j = 0; j<COLUNAS_MAPA; j++)
		{
			mapaMundi[i][j] = auxMapaMundi[i][j];
		}
	}

	//criando o objeto e enviando o array com as posicoes deste cenario MAPA MUNDI
	cenario = new Cenario(COLUNAS_MAPA, LINHAS_MAPA);
	(*cenario).initialize(mapaMundi);

	//desalocando
	for(int i = 0; i<LINHAS_MAPA; i++)
	{ 	
		free(mapaMundi[i]);
	}
	free(mapaMundi);


	//territorios
	i = 0;
	for(list<Territorio *>::iterator it = territorios.begin(); it != territorios.end(); it++, i++)
	{
		if(i==0)	//eua
		{
			//Declaracao dos tiles dos territorios
			(*(*it)).addTile((*cenario).tiles[4][4]);
			//lado
			(*(*it)).addTile((*cenario).tiles[5][4]);
			(*(*it)).addTile((*cenario).tiles[3][4]);
			//baixo
			(*(*it)).addTile((*cenario).tiles[4][5]);
			(*(*it)).addTile((*cenario).tiles[4][5]);
			//cima
			(*(*it)).addTile((*cenario).tiles[4][6]);
			(*(*it)).addTile((*cenario).tiles[4][6]);
		}
		if(i==1)	//siria
		{
			//(*(*it)).addTile((*cenario).tiles[20][5]);
			//(*(*it)).addTile((*cenario).tiles[21][5]);
			(*(*it)).addTile((*cenario).tiles[5][3]);
			(*(*it)).addTile((*cenario).tiles[6][3]);
		}
	}

	territorios.push_back(new Territorio("Canada"));
	(*territorios.back()).addTile((*cenario).tiles[4][7]);

	(*nacoes.front()).exercitoAdd(soldado,NULL,3,3);
	(*nacoes.front()).exercitoAdd(canhao,NULL,4,5);
	(*nacoes.front()).exercitoAdd(navio,NULL,5,1);
	(*nacoes.front()).exercitoAdd(aviao,NULL,6,7);

	(*nacoes.back()).exercitoAdd(soldado,NULL,24,16);
	(*nacoes.back()).exercitoAdd(canhao,NULL,18,18);
	(*nacoes.back()).exercitoAdd(navio,NULL,20,18);
	(*nacoes.back()).exercitoAdd(aviao,NULL,22,18);

	return 1;
}


int sendNetworkMessages()
{
	/*if ((*conexaoCliente).enviaJogada()) {
			return 1;	
	}*/
	return 0;
}

int do_miscAfter()
{
	sound();
	sendNetworkMessages();

	return 1;
}





