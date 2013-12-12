#include "Territorio.h"
#include "Tile.h"

Territorio::Territorio(string _nome)
{
	nome = _nome;
	nacao = NULL;
	pontosProducao = 0;
}

void Territorio::coletar()
{
	int petroleo = 5, ferro = 5, ouro = 5, madeira = 5;
	int bonusBase = 5, bonusEspecial = 15;

	pontosProducao++;

	//iterar todos e ir acumulando para a nacao
	for(list<Tile *>::iterator it = tiles.begin(); it != tiles.end(); it++)
	{
		switch( (*(*it)).tipo )
		{
		  case OCEANO:      //agua
			petroleo += bonusBase;
			ouro += bonusBase;
			break;
		  case TERRA:       //terra
			ferro += bonusBase;
			madeira += bonusBase;
			break;
		  case FLORESTA:      //arvore
			madeira += bonusEspecial;
			break;
		  case MINA_OURO:     //ouro
			ouro += bonusEspecial;
			break;
		  case PETROLEO:      //petroleo
			petroleo += bonusEspecial;
			break;
		  case MINA_FERRO:    //ferro
			ferro += bonusEspecial;
			break;
		  default:        //capital dah mais recursos?
			break;        
		}
	}

	(*nacao).petroleo += petroleo;
	(*nacao).ferro += ferro;
	(*nacao).ouro += ouro;
	(*nacao).madeira += madeira;
}

void Territorio::serConquistado(Nacao* _nacao)
{
	if(nacao != NULL)
	{
		for(list<Territorio *>::iterator it = (*nacao).territorios.begin(); it != (*nacao).territorios.end(); it++)
		{
			if( (*it) == this )
			{
				(*nacao).territorios.erase(it);
				break;
			}
		}
		(*nacao).carregaScore();
	}

  	nacao = _nacao;
  	(*nacao).territorios.push_back(this);
}

void Territorio::addTile(Tile* tile)
{
  tiles.push_back(tile);
  (*tile).territorio = this;
}

void Territorio::mostrarCapital()
{
  (*tiles.front()).showCapital();
}

void Territorio::criarUnidade(ClasseUnidade* classeUnidade)
{
	if(nacao == NULL)
		return;

	if(pontosProducao > (*classeUnidade).custoTurnos)
	{
		(*nacao).exercitoAdd(classeUnidade, this, NULL, NULL);
	}
	else
		cout << "Voce precisa aguardar mais alguns turnos para produzir esta unidade" << endl;
}


