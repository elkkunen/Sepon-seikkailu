// gcc main.c game_loop.c game_menu.c settings_menu.c -o game $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "game.h"

int winWidth, winHeight;
int highscore = 0;

Settings settings = {1};
Colors bgColors = {0};

void fileIO(bool mode, const char *filename, void *data, size_t dataSize) {
	FILE *fd;
	if (mode == READ) {
		fd = fopen(filename, "rb");
		if (!fd) return;
		fread(data, dataSize, 1, fd);
		fclose(fd);
	}
	else if (mode == WRITE) {
		fd = fopen(filename, "wb");
		fwrite(data, dataSize, 1, fd);
		fclose(fd);
	}
}

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

	fileIO(READ, SETTINGS_FILE, &settings, sizeof(settings));
	fileIO(READ, SCORE_FILE, &highscore, sizeof(highscore));

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *bgMusic = Mix_LoadMUS("audio/background.mp3");

	Mix_PlayMusic(bgMusic, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME * settings.music);

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
