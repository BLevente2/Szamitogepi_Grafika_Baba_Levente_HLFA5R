#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"    // vec3 most már innen jön

typedef struct {
    vec3 position;
} Camera;

extern Camera globalCamera;
extern vec3   globalTarget;

void init_camera(Camera* c);
void update_camera(Camera* c, vec3 target);
void apply_camera(void);

void adjust_camera_angle(float delta);
void adjust_camera_radius(float delta);

#endif /* CAMERA_H */