#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

SDL_Texture *createText(SDL_Renderer *rend, char *text, char *fontName, uint8_t fontSize, Colors *colors) {
    TTF_Font *font = TTF_OpenFont(fontName, fontSize);

    SDL_Color color = {colors->bgRed, colors->bgGreen, colors->bgBlue, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    const SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    return &texture;
}

void menuLoop(SDL_Window *window, SDL_Renderer *renderer) {
    Colors textColor = {0, 0, 255};
    SDL_Texture *texture = createText(renderer, "testi", "fonts/main.ttf", 32, &textColor);

    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    SDL_Rect dst = {100, 100, text_width, text_height};

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, bgColors.bgRed, bgColors.bgGreen, bgColors.bgBlue, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS cap, optional but recommended
    }
}