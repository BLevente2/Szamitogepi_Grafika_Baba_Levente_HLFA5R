#include "scene.h"
#include "rectangular_prism.h"
#include "player.h"
#include "obstacle.h"
#include "ground.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/* ------------------------------------------------ segédfüggvények --- */

/* Egyszerű AABB–AABB metszésvizsgálat két téglatest között                */
static bool aabb_intersect(const RectangularPrism* a,
                           const RectangularPrism* b)
{
    return fabsf(a->position.x - b->position.x) <
               (a->size.x + b->size.x) * 0.5f &&
           fabsf(a->position.y - b->position.y) <
               (a->size.y + b->size.y) * 0.5f &&
           fabsf(a->position.z - b->position.z) <
               (a->size.z + b->size.z) * 0.5f;
}

/* Játékos–akadály ütközés ellenőrzése                                     */
static bool check_player_obstacle_collision(const Player*    p,
                                            const Obstacle*  o)
{
    return aabb_intersect(&p->box, &o->box);
}

static void clear_obstacles(Scene* s)
{
    free(s->obstacles);
    s->obstacles     = NULL;
    s->obstacleCount = 0;
}

static float rand_float(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

/* Egyetlen akadály felhelyezése                                           */
static void spawn_obstacle(Scene* s)
{
    /* köv. akadály X 20-25 egységgel előrébb */
    s->nextObstacleX += rand_float(20.0f, 25.0f);

    vec3 size = {
        rand_float(s->player.box.size.x, s->player.box.size.x * 3.0f),
        rand_float(s->player.box.size.y, s->player.box.size.y * 2.0f),
        rand_float(s->player.box.size.z, s->player.box.size.z * 10.0f)
    };

    vec3 pos;
    pos.x = s->nextObstacleX;
    pos.y = size.y * 0.5f;

    float hw = s->ground.halfWidth;
    pos.z = rand_float(-hw + size.z * 0.5f, hw - size.z * 0.5f);

    s->obstacleCount++;
    s->obstacles = realloc(s->obstacles,
                           sizeof(Obstacle) * s->obstacleCount);

    init_obstacle(&s->obstacles[s->obstacleCount - 1],
                  pos,
                  size,
                  s->player.score);
}

/* ---------------------------------------------------------------------- */
/*                             Scene-kezelés                              */
/* ---------------------------------------------------------------------- */

void init_scene(Scene* s)
{
    srand((unsigned)time(NULL));

    float cube  = 1.0f;
    float halfH = cube * 0.5f;

    /* játékos */
    init_player(&s->player,
                (vec3){0.0f, halfH, 0.0f},
                cube,
                8.0f,      /* side move speed */
                40.0f,     /* max side speed  */
                0.1f);     /* lerp factor     */
    s->player.forwardSpeed = 4.0f;

    /* talaj textúrával */
    init_ground(&s->ground,
                cube * 20.0f,
                "assets/ground.bmp");

    s->obstacles      = NULL;
    s->obstacleCount  = 0;
    s->nextObstacleX  = s->player.box.position.x + 20.0f;

    while (s->nextObstacleX <
           s->player.box.position.x + INITIAL_OBSTACLE_REGION) {
        spawn_obstacle(s);
    }
}

void reset_scene(Scene* s)
{
    float halfH = s->player.box.size.y * 0.5f;
    vec3  start = {0.0f, halfH, 0.0f};

    clear_obstacles(s);

    s->player.box.position = start;
    s->player.forwardSpeed = 4.0f;
    s->player.score        = 0;

    s->nextObstacleX = start.x + 20.0f;
    while (s->nextObstacleX < start.x + INITIAL_OBSTACLE_REGION) {
        spawn_obstacle(s);
    }
}

/* Fő logikai frissítés – true: game over                                  */
bool update_scene(Scene* s, double dt)
{
    update_player(&s->player, dt);

    if (is_player_off_ground(&s->ground, &s->player))
        return true;

    for (int i = 0; i < s->obstacleCount; ++i) {
        if (check_player_obstacle_collision(&s->player,
                                            &s->obstacles[i]))
            return true;
    }

    /* feleslegessé vált akadályok kidobása */
    int write = 0;
    for (int i = 0; i < s->obstacleCount; ++i) {
        if (s->obstacles[i].box.position.x >=
            s->player.box.position.x - 10.0f)
        {
            s->obstacles[write++] = s->obstacles[i];
        }
    }
    s->obstacleCount = write;
    s->obstacles = realloc(s->obstacles,
                           sizeof(Obstacle) * s->obstacleCount);

    /* előre új akadályok */
    while (s->nextObstacleX <
           s->player.box.position.x + INITIAL_OBSTACLE_REGION) {
        spawn_obstacle(s);
    }

    s->player.score = (long)floorf(s->player.box.position.x);
    return false;
}

/* Rajzolás                                                                */
void render_scene(const Scene* s)
{
    draw_ground(&s->ground, s->player.box.position.x);

    for (int i = 0; i < s->obstacleCount; ++i) {
        draw_obstacle(&s->obstacles[i]);
    }
    draw_player(&s->player);
}