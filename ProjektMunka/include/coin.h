#ifndef COIN_H
#define COIN_H

#include <stdbool.h>          /* bool, true, false */
#include "rectangular_prism.h"
#include "player.h"

typedef struct {
    RectangularPrism hitbox;
    vec3  position;
    float radius;
    float thickness;
    float rotationY;
    float bobPhase;
    float baseY;
} Coin;

void init_coin(Coin* c, vec3 pos);
void update_coin(Coin* c, double dt);
void draw_coin(const Coin* c);
bool check_coin_collision(const Coin* c, const Player* p);

#endif