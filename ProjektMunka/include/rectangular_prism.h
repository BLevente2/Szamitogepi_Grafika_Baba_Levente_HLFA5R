#ifndef RECTANGULAR_PRISM_H
#define RECTANGULAR_PRISM_H

#include "types.h"

typedef struct {
    vec3  size;
    vec3  position;
    Color color;
    float rotationY;
} RectangularPrism;

void init_rectangular_prism(RectangularPrism* p,
                             float w, float h, float d,
                             Color col, vec3 pos);
void set_rectangular_prism_size(RectangularPrism* p, float w, float h, float d);
void set_rectangular_prism_color(RectangularPrism* p, Color c);
void set_rectangular_prism_rotation(RectangularPrism* p, float rotDeg);
void draw_rectangular_prism(const RectangularPrism* p);

#endif