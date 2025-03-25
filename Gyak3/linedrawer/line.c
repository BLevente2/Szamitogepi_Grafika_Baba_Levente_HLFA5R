#include "line.h"

Line createLine(SDL_Point start, SDL_Point end, Color color) {
    Line l;
    l.start = start;
    l.end = end;
    l.color = color;
    return l;
}

void drawLine(SDL_Renderer *renderer, Line line) {
    SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, 255);
    SDL_RenderDrawLine(renderer, line.start.x, line.start.y, line.end.x, line.end.y);
}