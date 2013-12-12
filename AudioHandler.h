#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include <thread>

using namespace std;

class AudioHandler{
	
	public:

		Mix_Music* music;
		Mix_Chunk* effect;

		int playMusic();
		int playMusicGame();
		int playMusicCreditos();
		int playMusicOpcoes();
		int playVoiceMenu();
		int playEscolhaNacao();
		int playEffect();
		int playEffect_Enemy();

		AudioHandler();
		void initialize();	
		void finalize();	
};


#endif 
