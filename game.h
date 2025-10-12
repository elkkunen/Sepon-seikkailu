#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct {
	uint8_t bgRed;
	uint8_t bgGreen;
	uint8_t bgBlue;
} Colors;

extern Colors bgColors;

extern void menuLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void mainLoop(SDL_Window *window, SDL_Renderer *renderer);

#endif