#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"

typedef struct {
	int x, y;
	int width, height;
	int health;
	Colors colors;
	SDL_Rect hitbox;
} Player;

typedef struct {
	int x, y;
	int width, height;
	Colors colors;
	SDL_Rect hitbox;
} Box;

enum Directions {
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

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

void defineBox(Box *box) {
	box->width = 32;
	box->height = 32;
	box->x = rand() % (winWidth - box->width);
	box->y = rand() % (winHeight - box->height);
	box->colors.red = rand() % 255;
	box->colors.green = rand() % 255;
	box->colors.blue = rand() % 255;
}

void drawPlayer(SDL_Renderer *rend, Player *player, SDL_Texture *image, int angle) {
	SDL_Rect pRect = {player->x, player->y, player->width, player->height};
	player->hitbox = pRect;
	if (image) {
		SDL_RenderCopyEx(rend, image, NULL, &pRect, angle, NULL, 0);
	}
	else {
		SDL_SetRenderDrawColor(rend, player->colors.red, player->colors.green, player->colors.blue, 255);
		SDL_RenderFillRect(rend, &pRect);
	}
}

void drawBox(SDL_Renderer *rend, Box *box) {
	SDL_Rect bRect = {box->x, box->y, box->width, box->height};
	box->hitbox = bRect;
	SDL_SetRenderDrawColor(rend, box->colors.red, box->colors.green, box->colors.blue, 255);
	SDL_RenderFillRect(rend, &bRect);
}

void gameLoop(SDL_Window *window, SDL_Renderer *renderer) {
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_Surface *surface = IMG_Load("src/images/Seppo.png");
	SDL_Texture *playerImage = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	Colors scoreColor = {255, 255, 255};
	SDL_Texture *scoreTexture = createText(renderer, "Score: 0", DEFAULT_FONT, 24, &scoreColor);
	SDL_Rect scoreTextBox = createTextBox(scoreTexture, 64, 5);

	Player player;
	definePlayer(&player);

	Box box;
	defineBox(&box);

	SDL_Event event;
	bool running = 1;
	
	int step = 10;
	int direction = UP;
	int score = 0;
	char scoreString[16];

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

		if (SDL_HasIntersection(&player.hitbox, &box.hitbox)) {
			switch (direction) {
				case UP: box.y -= step; break;
				case DOWN: box.y += step; break;
				case LEFT: box.x -= step; break;
				case RIGHT: box.x += step; break;
			}
		}

		if (box.y < 0 - box.height + 10 || box.y > winWidth - 10 || box.x < 0 - box.width + 10 || box.x > winHeight - 10) {
			score ++;
			sprintf(scoreString, "Score: %d", score);
			scoreTexture = createText(renderer, scoreString, DEFAULT_FONT, 24, &scoreColor);
			defineBox(&box);
		}

		SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
		SDL_RenderClear(renderer);

		drawBox(renderer, &box);
		drawPlayer(renderer, &player, playerImage, direction);

		SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreTextBox);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(playerImage);
	TTF_Quit();
	IMG_Quit();

	if (score > highscore) {
		highscore = score;
		fileIO(WRITE, SCORE_FILE, &highscore, sizeof(score));
	}
}