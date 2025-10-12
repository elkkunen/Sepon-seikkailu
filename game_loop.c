#include <SDL2/SDL.h>
#include "game.h"

typedef enum {
	STILL,
	UP,
	DOWN,
	LEFT,
	RIGHT
} Directions;

typedef struct {
	int x, y;
	int width, height;
	int health;
	Colors colors;
} Player;

int step = 5;
int winWidth, winHeight;

void definePlayer(Player *player) {
	player->x = winWidth / 2;
	player->y = winHeight / 2;
	player->width = 32;
	player->height = 32;
	player->health = 100;

	player->colors.bgRed = 255;
	player->colors.bgGreen = 255;
	player->colors.bgBlue = 255;
}

void drawPlayer(SDL_Renderer *rend, Player *player) {
	SDL_Rect pRect = {player->x, player->y, player->width, player->height};
	SDL_SetRenderDrawColor(rend, player->colors.bgRed, player->colors.bgGreen, player->colors.bgBlue, 255);
	SDL_RenderFillRect(rend, &pRect);
}

void mainLoop(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_GetWindowSize(window, &winWidth, &winHeight);

	Player player;
	definePlayer(&player);

	SDL_Event event;
	uint8_t running = 1;
	uint8_t direction = STILL;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_w: direction = UP; break;
					case SDLK_s: direction = DOWN; break;
					case SDLK_a: direction = LEFT; break;
					case SDLK_d: direction = RIGHT; break;
					case SDLK_SPACE: direction = STILL; break;
                    case SDLK_ESCAPE: return; break;
				}
			}
		}
		switch (direction) {
			case UP: 
				if (player.y > 0) {
					player.y -= step; 
				}
				break;
			case DOWN:
				if (player.y < winHeight - player.height) {
					player.y += step; 
				}
				break;
			case LEFT:
				if (player.x > 0) {
					player.x -= step;
				} 
				break;
			case RIGHT:
				if (player.x < winWidth - player.width) {
					player.x += step;
				}
				break;
		}

		SDL_SetRenderDrawColor(renderer, bgColors.bgRed, bgColors.bgGreen, bgColors.bgBlue, 255);
		SDL_RenderClear(renderer);

		drawPlayer(renderer, &player);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
}