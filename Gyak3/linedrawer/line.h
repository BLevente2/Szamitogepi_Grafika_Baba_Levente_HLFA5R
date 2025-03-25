#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include "color.h"

typedef struct {
    SDL_Point start;
    SDL_Point end;
    Color color;
} Line;

Line createLine(SDL_Point start, SDL_Point end, Color color);
void drawLine(SDL_Renderer *renderer, Line line);

#endif