#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "rectangular_prism.h"
#include <stdbool.h>

typedef struct {
    RectangularPrism box;
    vec3  velocity;          /* sebesség mindhárom tengelyen */
    float mass;
    bool  onGround;

    float lateralSpeed;      /* max oldal-sebesség */
    float maxForwardSpeed;   /* felső korlát előre */
    float forwardAcceleration;

    long  score;
    long  coins;
} Player;

void init_player(Player* player,
                 vec3    startPos,
                 float   cubeSize,
                 float   lateralSpeed,
                 float   maxForwardSpeed,
                 float   forwardAcceleration);

void update_player(Player* player,
                   double  deltaTime,
                   float   lateralInput);   /* –1 … +1 */

void draw_player(const Player* player);

#endif /* PLAYER_H */
