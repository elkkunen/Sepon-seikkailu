#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "game.h"

enum Settings {
    MUSIC,
    RESET,
    EXIT,
    SETTINGS_AMOUNT
};

void settingsLoop(SDL_Window *window, SDL_Renderer *renderer) {
    const char *toggleText[] = {"OFF", "ON"};
    char musicStateString[16];
    snprintf(musicStateString, sizeof(musicStateString), "MUSIC: %s", toggleText[settings.music]);

    char *settingsString[] = {musicStateString, "RESET GAME", "EXIT"};

    SDL_Texture *settingsTexture[SETTINGS_AMOUNT];
    SDL_Rect settingsButton[SETTINGS_AMOUNT];

    for (int i = 0; i < SETTINGS_AMOUNT; i ++) {
        settingsTexture[i] = createText(renderer, settingsString[i], DEFAULT_FONT, 32, &textColors);
        settingsButton[i] = createTextBox(settingsTexture[i], winWidth / 2, 60 + 60 * i);
    }

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
                        if (isMouseHovering(&settingsButton[MUSIC])) {
                            settings.music = !settings.music;
                            Mix_VolumeMusic(MIX_MAX_VOLUME * settings.music);
                            snprintf(musicStateString, sizeof(musicStateString), "Music: %s", toggleText[settings.music]);
                            settingsTexture[0] = createText(renderer, musicStateString, DEFAULT_FONT, 32, &textColors);
                            settingsButton[0] = createTextBox(settingsTexture[0], winWidth / 2, settingsButton[0].y);
                        }
                        else if (isMouseHovering(&settingsButton[RESET])) {
                            highscore = 0;
                            fileIO(WRITE, SCORE_FILE, &highscore, sizeof(highscore));
                        }
                        else if (isMouseHovering(&settingsButton[EXIT])) {
                            running = 0;
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

        for (int i = 0; i < SETTINGS_AMOUNT; i ++) {
            if (isMouseHovering(&settingsButton[i])) SDL_SetRenderDrawColor(renderer, 161, 161, 161, 255);
            else SDL_SetRenderDrawColor(renderer, bgColors.red, bgColors.green, bgColors.blue, 255);
            SDL_RenderFillRect(renderer, &settingsButton[i]);
            SDL_RenderCopy(renderer, settingsTexture[i], NULL, &settingsButton[i]);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    fileIO(WRITE, SETTINGS_FILE, &settings, sizeof(settings));

    for (int i = 0; i < SETTINGS_AMOUNT; i ++) {
        SDL_DestroyTexture(settingsTexture[i]);
    }
}