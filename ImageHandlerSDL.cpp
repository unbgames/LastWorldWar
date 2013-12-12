#include "ImageHandlerSDL.h"

ImageHandlerSDL::ImageHandlerSDL()
{
	
}

SDL_Surface * ImageHandlerSDL::load_image( string filename, Uint32 corTransparencia = 0) 
{
    //ponteiro para a imagem que sera carregada
    SDL_Surface* loadedImage = NULL;

    //ponteiro para a imagem optimizada caso seja possivel otimizar
    SDL_Surface* optimizedImage = NULL;

    //carregando a imagem (SDL_IMAGE)
    loadedImage = IMG_Load( filename.c_str() );

    //verificando erros no carregamento
    if( loadedImage != NULL )
    {
        //criando uma imagem otimizada
		if( ( filename.find(".png") > 0 || filename.find(".PNG") > 0 ) && corTransparencia != 0 )	//se encontrar a extensao png jah pega a componente alpha de transparencia
		{        
			optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
		}
		else
        	optimizedImage = SDL_DisplayFormat( loadedImage );

		//If the image was optimized just fine 
		if( optimizedImage != 0 ) 
		{
			//liberando a imagem nao otimizada e utilizando a otimizada
	        SDL_FreeSurface( loadedImage );
			loadedImage = optimizedImage;
		}

		if( corTransparencia != 0 )
		{
			//setando pixels da cor definida como transparentes
			SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, corTransparencia ); 
		}
    }

    //retornando a imagem
    return loadedImage;
}
