#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "color.h"

typedef struct {
    SDL_Point p1;
    SDL_Point p2;
    Color color;
} Rectangle;

Rectangle createRectangle(SDL_Point p1, SDL_Point p2, Color color);
void drawRectangle(SDL_Renderer *renderer, Rectangle rectangle);

#endif