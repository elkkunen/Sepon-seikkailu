#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	uint8_t bgRed;
	uint8_t bgGreen;
	uint8_t bgBlue;
} Colors;

extern Colors bgColors;

extern int winWidth, winHeight;

extern bool menuLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void gameLoop(SDL_Window *window, SDL_Renderer *renderer);

#endif