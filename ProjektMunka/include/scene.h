#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "player.h"
#include "ground.h"
#include "obstacle.h"
#include "coin.h"

#define INITIAL_OBSTACLE_REGION 100.0f

typedef struct {
    Ground    ground;
    Player    player;
    Obstacle* obstacles;
    int       obstacleCount;
    float     nextObstacleX;
    Coin*     coins;
    int       coinCount;
    float     nextCoinX;
} Scene;

void init_scene(Scene* s);
bool update_scene(Scene* s, double dt);
void render_scene(const Scene* s);
void reset_scene(Scene* s);

#endif