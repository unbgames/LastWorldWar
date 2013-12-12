#include "FontHandler.h" 

	FontHandler::FontHandler(){
	
	}

	void FontHandler::initialize(){
		
	font = TTF_OpenFont( "lazy.ttf", 28 );
    fontMenu = TTF_OpenFont( "lazy.ttf", 40);
	
    TTF_SetFontStyle(fontMenu, TTF_STYLE_BOLD);

	}


	void FontHandler::finalize(){
		
	TTF_CloseFont( font );
	TTF_CloseFont( fontMenu);
	}


