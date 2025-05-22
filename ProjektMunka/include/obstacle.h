#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <stdbool.h>
#include "rectangular_prism.h"
#include "player.h"

typedef struct {
    RectangularPrism box;
} Obstacle;

void init_obstacle(Obstacle* o, vec3 pos, vec3 size, long score);
void draw_obstacle(const Obstacle* o);
bool check_obstacle_collision(const Obstacle* o, const Player* p);

#endif