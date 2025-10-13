#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "game.h"

void settingsLoop(SDL_Window *window, SDL_Renderer *renderer) {
    TTF_Init();

    Colors textColor = {0, 0, 255};
    SDL_Texture *musicToggleTexture = createText(renderer, "Music:", DEFAULT_FONT, 32, &textColor);
    SDL_Rect musicToggleTextBox = createTextBox(musicToggleTexture, 20, 60);

    SDL_Texture *onText = createText(renderer, "ON", DEFAULT_FONT, 32, &textColor);
    SDL_Texture *offText = createText(renderer, "OFF", DEFAULT_FONT, 32, &textColor);

    SDL_Rect musicToggleButton = createTextBox(offText, 140, 60);

    bool running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button = SDL_BUTTON_LEFT) {
                        if (isMouseHovering(&musicToggleButton)) musicState = !musicState;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
                    break;
            }
        }

        if (!musicState) {
            Mix_VolumeMusic(0);
        }
        else {
            Mix_VolumeMusic(MIX_MAX_VOLUME);
        }

        SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, musicToggleTexture, NULL, &musicToggleTextBox);

        SDL_RenderFillRect(renderer, &musicToggleButton);
        if (musicState) SDL_RenderCopy(renderer, offText, NULL, &musicToggleButton);
        else SDL_RenderCopy(renderer, onText, NULL, &musicToggleButton);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(musicToggleTexture);
    TTF_Quit();
}