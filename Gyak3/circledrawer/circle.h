#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include "color.h"

typedef struct Circle {
    double x;
    double y;
    double radius;
    Color color;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius, Color color);
double calc_circle_area(const Circle* circle);
void draw_circle_outline_by_segments(SDL_Renderer *renderer, const Circle *circle, int segments);
void draw_circle_outline_by_angle(SDL_Renderer *renderer, const Circle *circle, double angle);
void draw_circle_outline_by_max_segment(SDL_Renderer *renderer, const Circle *circle, double maxSegmentLength);
int is_point_inside_circle(const Circle *circle, int x, int y);

#endif