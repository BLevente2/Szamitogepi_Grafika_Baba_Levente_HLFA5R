#ifndef TYPES_H
#define TYPES_H

/* 3-dimenziós vektor */
typedef struct {
    float x, y, z;
} vec3;

/* RGB-szín [0-1] tartományban */
typedef struct {
    float red, green, blue;
} Color;

#endif /* TYPES_H */