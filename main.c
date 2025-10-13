// gcc main.c game_loop.c game_menu.c settings_menu.c -o game $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <stdbool.h>
#include "game.h"

int winWidth, winHeight;
bool musicState = 1;

Colors bgColors = {0};

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if (argc > 1) {
		switch (argv[1][0]) {
			case 'r': bgColors = (Colors){166, 68, 51}; break;
			case 'g': bgColors = (Colors){66, 166, 51}; break;
			case 'b': bgColors = (Colors){51, 116, 166}; break;
			case 'w': bgColors = (Colors){255, 255, 255}; break;
		}
	}

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *bgMusic = Mix_LoadMUS("audio/background.mp3");

	
	
	Mix_PlayMusic(bgMusic, -1);

	SDL_Window *window = SDL_CreateWindow("Sepon Seikkailu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_GetWindowSize(window, &winWidth, &winHeight);

	bool gameRunning;
	do {
		gameRunning = menuLoop(window, renderer);
	} while (gameRunning);

	Mix_FreeMusic(bgMusic);
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
