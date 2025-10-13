#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEADER_FONT "fonts/Header.ttf"
#define DEFAULT_FONT "fonts/Buttons.ttf"

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Colors;

extern Colors bgColors;

extern int winWidth, winHeight;
extern bool musicState;

extern bool menuLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void gameLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void settingsLoop(SDL_Window *window, SDL_Renderer *renderer);

extern bool isMouseHovering(SDL_Rect *rect);

extern SDL_Texture *createText(SDL_Renderer *rend, char *text, char *fontName, uint8_t fontSize, Colors *colors);
extern SDL_Rect createTextBox(SDL_Texture *texture, int x, int y);

#endif