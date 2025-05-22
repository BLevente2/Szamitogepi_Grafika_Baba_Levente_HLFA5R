#ifndef GROUND_H
#define GROUND_H

#include <stdbool.h>
#include <GL/gl.h>
#include "player.h"

typedef struct {
    float  width;
    float  halfWidth;
    GLuint texture;
    float  repeatX;
    float  repeatZ;
} Ground;

void  init_ground(Ground* g,float width,const char* texturePath);
void  draw_ground(const Ground* g,float centerX);
bool  is_player_off_ground(const Ground* g,const Player* p);

#endif