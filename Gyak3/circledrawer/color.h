#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

Color createColor(Uint8 r, Uint8 g, Uint8 b);

#endif