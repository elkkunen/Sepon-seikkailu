#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEADER_FONT "src/fonts/Header.ttf"
#define DEFAULT_FONT "src/fonts/Buttons.ttf"

#define SETTINGS_FILE "settings.bin"
#define SCORE_FILE "score.bin"

#define READ 0
#define WRITE 1

typedef struct {
	bool music;
} Settings;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Colors;

extern Settings settings;
extern Colors bgColors;

extern int winWidth, winHeight;
extern int highscore;

extern bool menuLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void gameLoop(SDL_Window *window, SDL_Renderer *renderer);
extern void settingsLoop(SDL_Window *window, SDL_Renderer *renderer);

extern void fileIO(bool mode, const char *filename, void *data, size_t dataSize);
extern bool isMouseHovering(SDL_Rect *rect);

extern SDL_Texture *createText(SDL_Renderer *rend, char *text, char *fontName, uint8_t fontSize, Colors *colors);
extern SDL_Rect createTextBox(SDL_Texture *texture, int x, int y);

#endif