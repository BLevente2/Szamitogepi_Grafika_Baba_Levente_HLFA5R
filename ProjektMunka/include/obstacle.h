#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <stdbool.h>
#include "types.h"             /* vec3 */
#include "rectangular_prism.h"
#include "player.h"            /* a teljes Player definícióhoz */

/* Akadály – fizikailag is mozoghat, ha a Player meglöki */
typedef struct {
    RectangularPrism box;   /* geometria + szín */
    vec3  velocity;         /* sebesség (x,y,z) */
    float mass;             /* tömeg – impulzus átadáshoz */
} Obstacle;

/* Inicializálásnál a score-függő színt is beállítjuk */
void init_obstacle(Obstacle* o, vec3 pos, vec3 size, long score);

/* Pozíció- és sebességfrissítés minden képkockában */
void update_obstacle(Obstacle* o, double dt);

/* Kirajzolás */
void draw_obstacle(const Obstacle* o);

/* AABB-ütközés teszt Playerrel */
bool check_obstacle_collision(const Obstacle* o, const Player* p);

#endif /* OBSTACLE_H */
