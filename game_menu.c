#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "game.h"

typedef enum {
    START_BTN,
    SETTINGS_BTN,
    EXIT_BTN,
    BUTTON_AMOUNT
} Buttons;

typedef enum {
    MENU,
    EXIT,
    GAME,
    SETTINGS
} Modes;

bool isMouseHovering(SDL_Rect *rect) {
    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);
    return mousex >= rect->x && mousex <= rect->x + rect->w && mousey >= rect->y && mousey <= rect->y + rect->h;
}

SDL_Texture *createText(SDL_Renderer *rend, char *text, char *fontName, uint8_t fontSize, Colors *colors) {
    TTF_Font *font = TTF_OpenFont(fontName, fontSize);

    SDL_Color color = {colors->bgRed, colors->bgGreen, colors->bgBlue, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Rect createTextBox(SDL_Texture *texture, int x, int y) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect dst = {x, y, w, h};

    return dst;
}

int winWidth, winHeight;

bool menuLoop(SDL_Window *window, SDL_Renderer *renderer) {
    TTF_Init();
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    SDL_Texture *texture[BUTTON_AMOUNT];
    SDL_Rect button[BUTTON_AMOUNT];

    Colors textColor = {0, 0, 0};
    char *buttonTexts[] = {"START", "SETTINGS", "EXIT"};

    for (int i = 0; i < BUTTON_AMOUNT; i ++) {
        texture[i] = createText(renderer, buttonTexts[i], "fonts/main.ttf", 32, &textColor);
        button[i] = createTextBox(texture[i], (winWidth - 125) / 2, 40 + 80 * i);
    }

    SDL_Event event;
    uint8_t mode = MENU;

    while (mode == MENU) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    mode = EXIT;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (isMouseHovering(&button[START_BTN])) mode = GAME;
                        else if (isMouseHovering(&button[SETTINGS_BTN])) mode = MENU;
                        else if (isMouseHovering(&button[EXIT_BTN])) mode = EXIT;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            mode = EXIT;
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, bgColors.bgRed, bgColors.bgGreen, bgColors.bgBlue, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < BUTTON_AMOUNT; i ++) {
            if (isMouseHovering(&button[i])) SDL_SetRenderDrawColor(renderer, 161, 161, 161, 255);
            else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &button[i]);
            SDL_RenderCopy(renderer, texture[i], NULL, &button[i]);
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    for (int i = 0; i < BUTTON_AMOUNT; i ++) {
        SDL_DestroyTexture(texture[i]);
    }
    TTF_Quit();
    switch (mode) {
        case GAME:
            gameLoop(window, renderer);
            break;
        case EXIT:
            return 0;
            break;
    }
    return 1;
}