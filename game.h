#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Colors;

extern Colors bgColors;

extern int winWidth, winHeight;

extern bool menuLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void gameLoop(SDL_Window *window, SDL_Renderer *renderer);

#endif