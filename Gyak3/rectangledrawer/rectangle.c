#include "rectangle.h"
#include <stdlib.h>

Rectangle createRectangle(SDL_Point p1, SDL_Point p2, Color color) {
    Rectangle r;
    r.p1 = p1;
    r.p2 = p2;
    r.color = color;
    return r;
}

void drawRectangle(SDL_Renderer *renderer, Rectangle rectangle) {
    int x = rectangle.p1.x < rectangle.p2.x ? rectangle.p1.x : rectangle.p2.x;
    int y = rectangle.p1.y < rectangle.p2.y ? rectangle.p1.y : rectangle.p2.y;
    int w = abs(rectangle.p1.x - rectangle.p2.x);
    int h = abs(rectangle.p1.y - rectangle.p2.y);
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, rectangle.color.r, rectangle.color.g, rectangle.color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}