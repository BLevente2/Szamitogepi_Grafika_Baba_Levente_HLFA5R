#ifndef PALETTE_H
#define PALETTE_H

#include <SDL2/SDL.h>
#include "color.h"

#define PALETTE_COLOR_COUNT 5

typedef struct {
    Color colors[PALETTE_COLOR_COUNT];
    SDL_Rect rects[PALETTE_COLOR_COUNT];
} Palette;

Palette createPalette(int x, int y, int width, int height, int spacing);
void drawPalette(SDL_Renderer *renderer, Palette palette);
int getPaletteColorIndex(Palette palette, int mouseX, int mouseY);

#endif