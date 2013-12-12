#ifndef IMAGEHANDLERSDL_H
#define IMAGEHANDLERSDL_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;

class ImageHandlerSDL
{
	public:
		ImageHandlerSDL();
		SDL_Surface *load_image(string, Uint32);
};

#endif
