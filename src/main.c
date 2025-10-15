// gcc src/*.c -o game $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "game.h"

int winWidth, winHeight;
int highscore = 0;

Settings settings = {1};
Colors bgColors = {0};
Colors textColors = {255};

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

int main() {
	srand(time(NULL));

	fileIO(READ, SETTINGS_FILE, &settings, sizeof(settings));
	fileIO(READ, SCORE_FILE, &highscore, sizeof(highscore));

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *bgMusic = Mix_LoadMUS("src/audio/background.mp3");

	Mix_PlayMusic(bgMusic, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME * settings.music);

	SDL_Window *window = SDL_CreateWindow("Sepon Seikkailu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_GetWindowSize(window, &winWidth, &winHeight);

	bool gameRunning;
	do {
		gameRunning = menuLoop(window, renderer);
	} while (gameRunning);

	Mix_FreeMusic(bgMusic);
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	return 0;
}
