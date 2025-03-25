#include "sphere.h"
#include <GL/gl.h>
#include <math.h>
#include <SDL2/SDL.h>

static float sphere_rotation = 0.0f;
static Uint32 last_time = 0;
static const int slices = 10;
static const int stacks = 10;

void init_sphere(){
    last_time = SDL_GetTicks();
}

void sphere_update(){
    Uint32 current_time = SDL_GetTicks();
    float delta = (current_time - last_time) / 1000.0f;
    last_time = current_time;
    sphere_rotation += 30.0f * delta;
    if(sphere_rotation > 360.0f)
        sphere_rotation -= 360.0f;
}

void sphere_draw(){
    glPushMatrix();
    glRotatef(sphere_rotation, 0, 0, 1);
    glColor3f(0.5, 0.5, 0.5);
    int i, j;
    for(i = 0; i < stacks; i++){
        float lat0 = M_PI * (-0.5 + (float)i / stacks);
        float lat1 = M_PI * (-0.5 + (float)(i+1) / stacks);
        float sinLat0 = sin(lat0);
        float cosLat0 = cos(lat0);
        float sinLat1 = sin(lat1);
        float cosLat1 = cos(lat1);
        glBegin(GL_TRIANGLE_STRIP);
        for(j = 0; j <= slices; j++){
            float lng = 2 * M_PI * (float)j / slices;
            float sinLng = sin(lng);
            float cosLng = cos(lng);
            float x = cosLat0 * cosLng;
            float y = cosLat0 * sinLng;
            float z = sinLat0;
            glVertex3f(x, y, z);
            x = cosLat1 * cosLng;
            y = cosLat1 * sinLng;
            z = sinLat1;
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    glPopMatrix();
}