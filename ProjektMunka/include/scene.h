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

    /* dinamikus akadály-tömb */
    Obstacle* obstacles;
    int       obstacleCount;
    float     nextObstacleX;

    /* dinamikus érme-tömb */
    Coin*     coins;
    int       coinCount;
    float     nextCoinX;

    /* új állapot-tagok a “késleltetett game-over” logikához */
    bool   lost;        /* igaz, miután leesett vagy ütközött */
    double lostTimer;   /* hátralévő idő a game-over képernyőig (s) */
} Scene;

/*  az új függvény-szignatúra – átadjuk a laterális bemenetet  */
void init_scene(Scene* s);
void reset_scene(Scene* s);
bool  update_scene(Scene* s,double dt,float lateralInput);
void  render_scene(const Scene* s);

#endif /* SCENE_H */
