#include "Unidade.h"
#include "Nacao.h"
#include "Tile.h"

ClasseUnidade::ClasseUnidade(string _nome, int _qtdMovimentos, int _forca, int _ambiente, int _custoFerro, int _custoOuro, int _custoMadeira, int _custoPetroleo, int _custoTurnos )
{
	nome = _nome;
	forca = _forca;
	qtdMovimentos = _qtdMovimentos;
	ambiente = _ambiente;

	custoFerro = _custoFerro;
	custoOuro = _custoOuro;
	custoMadeira = _custoMadeira;
	custoPetroleo = _custoPetroleo;

	custoTurnos = _custoTurnos;
}

