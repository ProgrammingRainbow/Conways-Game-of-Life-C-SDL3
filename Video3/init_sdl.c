#include "init_sdl.h"

bool game_init_sdl(struct Game *g) {
    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error initializing SDL2. %s\n", SDL_GetError());
        return false;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!g->window) {
        fprintf(stderr, "Error creating SDL_Window. %s\n", SDL_GetError());
        return false;
    }

    g->renderer = SDL_CreateRenderer(g->window, NULL);
    if (!g->renderer) {
        fprintf(stderr, "Error creating SDL_Renderer. %s\n", SDL_GetError());
        return false;
    }

    SDL_Surface *icon_surf = IMG_Load("images/icon.png");
    if (!icon_surf) {
        fprintf(stderr, "Error loading SDL_Surface. %s\n", SDL_GetError());
        return false;
    }
    SDL_SetWindowIcon(g->window, icon_surf);
    SDL_DestroySurface(icon_surf);
    icon_surf = NULL;

    return true;
}
