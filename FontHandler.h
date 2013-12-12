#ifndef FONTHANDLER_H
#define FONTHANDLER_H  

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

using namespace std;

class FontHandler{
	
	public:
		TTF_Font *font; 
		TTF_Font *fontMenu;
		
		FontHandler();

		 void initialize();	
		 void finalize();	

};

#endif 
