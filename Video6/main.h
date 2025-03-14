#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_FLAGS SDL_INIT_VIDEO
#define IMG_FLAGS IMG_INIT_PNG

#define WINDOW_TITLE "Conway's Game of Life"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define CELL_SIZE 10
#define CELL_PADDING 1

#define RENDERER_COLOR 0, 0, 0, 255
#define CELL_COLOR 128, 128, 128, 255

#define TARGET_DURATION 128

#define FONT_SIZE 32
#define FONT_COLOR (SDL_Color){255, 255, 255, 255}

#endif
