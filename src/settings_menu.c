#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "game.h"

void settingsLoop(SDL_Window *window, SDL_Renderer *renderer) {
    TTF_Init();

    const char *toggleText[] = {"OFF", "ON"};
    char musicStateString[16];

    Colors textColor = {0, 0, 255};
    sprintf(musicStateString, "Music: %s", toggleText[settings.music]);
    SDL_Texture *musicToggleTexture = createText(renderer, musicStateString, DEFAULT_FONT, 32, &textColor);
    SDL_Rect musicToggleTextBox = createTextBox(musicToggleTexture, winWidth / 2, 60);

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
                        if (isMouseHovering(&musicToggleTextBox)) {
                            settings.music = !settings.music;
                            Mix_VolumeMusic(MIX_MAX_VOLUME * settings.music);
                            sprintf(musicStateString, "Music: %s", toggleText[settings.music]);
                            musicToggleTexture = createText(renderer, musicStateString, DEFAULT_FONT, 32, &textColor);
                        }
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

        SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
        SDL_RenderClear(renderer);

        SDL_RenderFillRect(renderer, &musicToggleTextBox);
        SDL_RenderCopy(renderer, musicToggleTexture, NULL, &musicToggleTextBox);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    fileIO(WRITE, SETTINGS_FILE, &settings, sizeof(settings));

    SDL_DestroyTexture(musicToggleTexture);
    TTF_Quit();
}