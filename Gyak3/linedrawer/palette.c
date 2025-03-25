#include "palette.h"

Palette createPalette(int x, int y, int width, int height, int spacing) {
    Palette p;
    p.colors[0] = createColor(255, 0, 0);
    p.colors[1] = createColor(0, 255, 0);
    p.colors[2] = createColor(0, 0, 255);
    p.colors[3] = createColor(255, 255, 0);
    p.colors[4] = createColor(255, 0, 255);
    for (int i = 0; i < PALETTE_COLOR_COUNT; i++) {
        p.rects[i].x = x + i * (width + spacing);
        p.rects[i].y = y;
        p.rects[i].w = width;
        p.rects[i].h = height;
    }
    return p;
}

void drawPalette(SDL_Renderer *renderer, Palette palette) {
    for (int i = 0; i < PALETTE_COLOR_COUNT; i++) {
        SDL_SetRenderDrawColor(renderer, palette.colors[i].r, palette.colors[i].g, palette.colors[i].b, 255);
        SDL_RenderFillRect(renderer, &palette.rects[i]);
    }
}

int getPaletteColorIndex(Palette palette, int mouseX, int mouseY) {
    for (int i = 0; i < PALETTE_COLOR_COUNT; i++) {
        if (mouseX >= palette.rects[i].x && mouseX <= palette.rects[i].x + palette.rects[i].w &&
            mouseY >= palette.rects[i].y && mouseY <= palette.rects[i].y + palette.rects[i].h) {
            return i;
        }
    }
    return -1;
}