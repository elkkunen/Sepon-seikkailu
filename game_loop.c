#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

typedef struct {
	int x, y;
	int width, height;
	int health;
	Colors colors;
} Player;

typedef enum {
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
} Directions;

void definePlayer(Player *player) {
	player->x = winWidth / 2;
	player->y = winHeight / 2;
	player->width = 64;
	player->height = 64;
	player->health = 100;

	player->colors.red = 255;
	player->colors.green = 255;
	player->colors.blue = 255;
}

void drawPlayer(SDL_Renderer *rend, Player *player, SDL_Texture *image, int angle) {
	SDL_Rect pRect = {player->x, player->y, player->width, player->height};
	if (image) {
		SDL_RenderCopyEx(rend, image, NULL, &pRect, angle, NULL, 0);
	}
	else {
		SDL_SetRenderDrawColor(rend, player->colors.red, player->colors.green, player->colors.blue, 255);
		SDL_RenderFillRect(rend, &pRect);
	}
}

void gameLoop(SDL_Window *window, SDL_Renderer *renderer) {
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface *surface = IMG_Load("images/Seppo.png");
	SDL_Texture *playerImage = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Player player;
	definePlayer(&player);

	SDL_Event event;
	uint8_t running = 1;
	
	int step = 10;
	int direction = UP;

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_w:
							if (player.y > 0) {
								player.y -= step;
								direction = UP;
							}
							break;
						case SDLK_s:
							if (player.y < winHeight - player.height) {
								player.y += step;
								direction = DOWN;
							}
							break;
						case SDLK_a:
							if (player.x > 0) {
								player.x -= step;
								direction = LEFT;
							}
							break;
						case SDLK_d:
							if (player.x < winWidth - player.width) {
								player.x += step;
								direction = RIGHT;
							}
							break;
						case SDLK_ESCAPE: running = 0; break;
					}
			}
		}

		SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
		SDL_RenderClear(renderer);

		drawPlayer(renderer, &player, playerImage, direction);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
	SDL_DestroyTexture(playerImage);
}