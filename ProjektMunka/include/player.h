#ifndef PLAYER_H
#define PLAYER_H

#include "rectangular_prism.h"

typedef struct Player {
    RectangularPrism box;
    long             score;
    float            lateralSpeed;
    float            forwardSpeed;
    float            maxForwardSpeed;
    float            forwardAcceleration;
} Player;

void init_player(Player* player,
                 vec3    startPos,
                 float   cubeSize,
                 float   lateralSpeed,
                 float   maxForwardSpeed,
                 float   forwardAcceleration);
void update_player(Player* player, double deltaTime);
void draw_player(const Player* player);

#endif