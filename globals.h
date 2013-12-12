#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "ImageHandlerSDL.h"
#include "SDL/SDL_mixer.h"
#include "Draw.h"
#include "Random.h"
#include "Timer.h"
#include "AudioHandler.h"
#include "FontHandler.h"

extern SDL_Surface *screen;
extern SDL_Event event;
extern SDL_Rect rect;

extern bool quit;
extern bool gameOver;
extern int quadroEstado;
extern const int FRAMES_PER_SECOND;
extern int frame;

extern ImageHandlerSDL* ImageHandlerSDLObj;
extern Draw* drawObj;
extern Random* randomObj;
extern Timer* timer;
extern AudioHandler* audioHandler;
extern FontHandler* fontHandler;

extern bool meuTurno;

#endif
