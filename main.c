// gcc main.c game_loop.c game_menu.c -o game $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdbool.h>
#include "game.h"

Colors bgColors = {0};

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if (argc > 1) {
		switch (argv[1][0]) {
			case 'r': bgColors = (Colors){166, 68, 51}; break;
			case 'g': bgColors = (Colors){66, 166, 51}; break;
			case 'b': bgColors = (Colors){51, 116, 166}; break;
		}
	}

	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool gameRunning;
	do {
		gameRunning = menuLoop(window, renderer);
	} while (gameRunning);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
