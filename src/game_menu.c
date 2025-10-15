#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"

enum  Buttons {
    START_BTN,
    SETTINGS_BTN,
    EXIT_BTN,
    BUTTON_AMOUNT
};

enum Modes {
    GAME,
    SETTINGS,
    EXIT,
    MENU
};

bool isMouseHovering(SDL_Rect *rect) {
    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);
    return mousex >= rect->x && mousex <= rect->x + rect->w && mousey >= rect->y && mousey <= rect->y + rect->h;
}

SDL_Texture *createText(SDL_Renderer *rend, char *text, char *fontName, uint8_t fontSize, Colors *colors) {
    TTF_Font *font = TTF_OpenFont(fontName, fontSize);

    SDL_Color color = {colors->red, colors->green, colors->blue, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Rect createTextBox(SDL_Texture *texture, int x, int y) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect rect = {x - w / 2, y, w, h};

    return rect;
}

bool menuLoop(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Texture *headerTexture = createText(renderer, "SEPON SEIKKAILU", HEADER_FONT, 56, &textColors);
    SDL_Rect headerTextBox = createTextBox(headerTexture, winWidth / 2, 40);

    char highscoreString[16];
    snprintf(highscoreString, sizeof(highscoreString), "HIGHSCORE: %d", highscore);
    SDL_Texture *highscoreTexture = createText(renderer, highscoreString, DEFAULT_FONT, 32, &textColors);
    SDL_Rect highscoreTextBox = createTextBox(highscoreTexture, winWidth / 2, 130);

    SDL_Rect buttonsRect = {winWidth / 2 - 100, winHeight / 2 - 70, 200, 200};

    SDL_Texture *btnTexture[BUTTON_AMOUNT];
    SDL_Rect button[BUTTON_AMOUNT];

    char *buttonTexts[] = {"START", "SETTINGS", "EXIT"};

    for (int i = 0; i < BUTTON_AMOUNT; i ++) {
        btnTexture[i] = createText(renderer, buttonTexts[i], DEFAULT_FONT, 32, &textColors);
        button[i] = createTextBox(btnTexture[i], winWidth / 2, buttonsRect.y + 25 + 60 * i);
    }

    SDL_Event event;
    uint8_t mode = MENU;

    while (mode == MENU) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: mode = EXIT; break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < BUTTON_AMOUNT; i ++) {
                            if (isMouseHovering(&button[i])) mode = i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: mode = EXIT; break;
                        case SDLK_SPACE:
                        case SDLK_RETURN: 
                            mode = GAME; 
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 201, 201, 201, 100);
        SDL_RenderFillRect(renderer, &buttonsRect);

        SDL_RenderCopy(renderer, headerTexture, NULL, &headerTextBox);
        SDL_RenderCopy(renderer, highscoreTexture, NULL, &highscoreTextBox);

        for (int i = 0; i < BUTTON_AMOUNT; i ++) {
            if (isMouseHovering(&button[i])) SDL_SetRenderDrawColor(renderer, 161, 161, 161, 255);
            else SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
            SDL_RenderFillRect(renderer, &button[i]);
            SDL_RenderCopy(renderer, btnTexture[i], NULL, &button[i]);
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(headerTexture);
    SDL_DestroyTexture(highscoreTexture);
    for (int i = 0; i < BUTTON_AMOUNT; i ++) {
        SDL_DestroyTexture(btnTexture[i]);
    }

    switch (mode) {
        case GAME:
            bool retryGame;
            do {
                retryGame = gameLoop(window, renderer);
            } while (retryGame);
            return 1;
            break;
        case SETTINGS:
            settingsLoop(window, renderer);
            return 1;
            break;
    }
    return 0;
}