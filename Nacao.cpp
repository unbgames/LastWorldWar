#include "Nacao.h"
#include "Tile.h"
#include "Unidade.h" 
#include "ClasseUnidade.h" 
#include "Territorio.h"

#define AVIAO 0
#define NAVIO 1
#define SOLDADO 2
#define CANHAO 3

Nacao::Nacao(int _petroleo, int _madeira, int _ouro, int _ferro, string _nome, Uint32 _cor)
{
	petroleo = _petroleo;
	madeira = _madeira;
	ouro = _ouro;
	ferro = _ferro;

	nome = _nome;
	cor = _cor;
	
	qtdNacao[0] = 0;
	qtdNacao[1] = 0;
	qtdNacao[2] = 0;
	qtdNacao[3] = 0;
}

void Nacao::contarExercito()
{	
	int i;
	
	for(i=0;i<4;i++)
		qtdNacao[i] = 0;	
	
	for(list<Unidade *>::iterator it = exercito.begin(); it != exercito.end(); it++)
	{
		if ((*(*it)).isDead)
			continue;

		if ( (*(*it)).tipo == soldado)
			qtdNacao[SOLDADO]++;   
		else if ( (*(*it)).tipo == canhao)
			qtdNacao[CANHAO]++;   
		else if ( (*(*it)).tipo == navio)
			qtdNacao[NAVIO]++;   
		else if ( (*(*it)).tipo == aviao)
			qtdNacao[AVIAO]++;
	}
}


void Nacao::exercitoAdd(ClasseUnidade* classeUnidade, Territorio* territorio, int posX, int posY)
{
	if(	(*classeUnidade).custoPetroleo > petroleo || (*classeUnidade).custoOuro > ouro || 
		(*classeUnidade).custoFerro > ferro || (*classeUnidade).custoMadeira > madeira )
	{
		cout << "Não há recursos o suficiente para criacao da unidade " << (*classeUnidade).nome << endl;
	}
	else
	{
		if(territorio != NULL)
		{
			posX = (*(*territorio).tiles.front()).posX;
			posY = (*(*territorio).tiles.front()).posY;

			if( (*(*cenario).tiles[posY][posX]).ocupante != NULL )
			{
				cout << "Local onde a unidade sera criada jah tem uma unidade, retire-a para criar uma nova unidade" << endl;
				return;
			}
			(*territorio).pontosProducao -= (*classeUnidade).custoTurnos;
		}
		exercito.push_back(new Unidade(posX, posY, classeUnidade, this) );
		(*(*cenario).tiles[posY][posX]).ocupante = exercito.back();

		petroleo -= (*classeUnidade).custoPetroleo;
		ferro -= (*classeUnidade).custoFerro;
		ouro -= (*classeUnidade).custoOuro;
		madeira -= (*classeUnidade).custoMadeira;		
	}
	
	contarExercito();
}

void Nacao::exercitoPop()
{
	exercito.pop_front();
}


void Nacao::carregaScore()
{
	SDL_Color textColor = {255, 255, 255, 255};
	
	sprintf(scoreRecursosNacao,"%s -> Madeira: %d Ferro: %d Ouro: %d Petroleo: %d",nome.c_str(),madeira,ferro,ouro,petroleo);
	
	sprintf(scoreUnidadesNacao,"%s -> Soldado: %d Navio: %d Canhao: %d Aviao: %d",nome.c_str(),qtdNacao[SOLDADO],qtdNacao[NAVIO],qtdNacao[CANHAO],qtdNacao[AVIAO]);
	
	sprintf(scoreTerritoriosNacao,"Quantidade de Territorios: %d", Nacao::contarTerritorios());

	messageRecursos = TTF_RenderText_Solid( (*fontHandler).font, scoreRecursosNacao,textColor );
	messageUnidades = TTF_RenderText_Solid( (*fontHandler).font, scoreUnidadesNacao,textColor );
	messageTerritorios = TTF_RenderText_Solid( (*fontHandler).font, scoreTerritoriosNacao,textColor );
}


int Nacao::contarTerritorios()
{
	int i = 0;
	for(list<Territorio *>::iterator it = territorios.begin(); it != territorios.end(); it++, i++);

	return i;
}

void Nacao::coletar()
{
	for(list<Territorio *>::iterator it = territorios.begin(); it != territorios.end(); it++)
	{
		(*(*it)).coletar();
	}
}

void Nacao::finalize()
{
	while (!exercito.empty())
	{
		(*exercito.front()).finalize();
		delete( exercito.front() );
		exercito.pop_front();
	}
	while (!territorios.empty())
		territorios.pop_front();
}

void Nacao::atualizaQuadroExercito()
{
	for(list<Unidade *>::iterator it = exercito.begin(); it != exercito.end(); it++)
	{
		(*(*it)).atualizaAnimacao();
	}
}

