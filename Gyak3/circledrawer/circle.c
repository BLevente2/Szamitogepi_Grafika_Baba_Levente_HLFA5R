#include "circle.h"
#include <math.h>
#include <SDL2/SDL.h>

void set_circle_data(Circle* circle, double x, double y, double radius, Color color) {
    circle->x = x;
    circle->y = y;
    if (radius > 0.0) {
        circle->radius = radius;
    } else {
        circle->radius = NAN;
    }
    circle->color = color;
}

double calc_circle_area(const Circle* circle) {
    return circle->radius * circle->radius * M_PI;
}

void draw_circle_outline_by_segments(SDL_Renderer *renderer, const Circle *circle, int segments) {
    if (segments < 3) segments = 3;
    double angleStep = 2 * M_PI / segments;
    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, 255);
    for (int i = 0; i < segments; i++) {
        double angle1 = i * angleStep;
        double angle2 = (i + 1) * angleStep;
        int x1 = (int)(circle->x + circle->radius * cos(angle1));
        int y1 = (int)(circle->y + circle->radius * sin(angle1));
        int x2 = (int)(circle->x + circle->radius * cos(angle2));
        int y2 = (int)(circle->y + circle->radius * sin(angle2));
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void draw_circle_outline_by_angle(SDL_Renderer *renderer, const Circle *circle, double angle) {
    if (angle <= 0) angle = 0.1;
    int segments = (int)ceil((2 * M_PI) / angle);
    draw_circle_outline_by_segments(renderer, circle, segments);
}

void draw_circle_outline_by_max_segment(SDL_Renderer *renderer, const Circle *circle, double maxSegmentLength) {
    if (maxSegmentLength <= 0) maxSegmentLength = 1;
    double theta = 2 * asin(maxSegmentLength / (2 * circle->radius));
    if (theta <= 0) theta = 0.1;
    int segments = (int)ceil((2 * M_PI) / theta);
    draw_circle_outline_by_segments(renderer, circle, segments);
}

int is_point_inside_circle(const Circle *circle, int x, int y) {
    double dx = x - circle->x;
    double dy = y - circle->y;
    return (dx * dx + dy * dy) <= (circle->radius * circle->radius);
}