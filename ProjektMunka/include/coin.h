#ifndef COIN_H
#define COIN_H

#include "types.h"
#include "rectangular_prism.h"
#include "player.h"
#include "model.h"

typedef struct {
    float radius;
    float thickness;
    vec3  position;
    float rotationY;
    float bobPhase;
    float baseY;
    RectangularPrism hitbox;
} Coin;

void load_coin_model(const char* path);
void unload_coin_model(void);
void init_coin(Coin* c, vec3 pos);
void update_coin(Coin* c, double dt);
void draw_coin(const Coin* c);
bool check_coin_collision(const Coin* c, const Player* p);

#endif