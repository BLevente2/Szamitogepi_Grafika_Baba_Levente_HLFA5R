#include "scene.h"
#include "config.h"
#include "rectangular_prism.h"
#include "player.h"
#include "obstacle.h"
#include "coin.h"
#include "ground.h"
#include "skybox.h"
#include "camera.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

static bool aabb_intersect(const RectangularPrism* a, const RectangularPrism* b) {
    return fabsf(a->position.x - b->position.x) < (a->size.x + b->size.x) * 0.5f
        && fabsf(a->position.y - b->position.y) < (a->size.y + b->size.y) * 0.5f
        && fabsf(a->position.z - b->position.z) < (a->size.z + b->size.z) * 0.5f;
}

static bool player_hits_obstacle(const Player* p, const Obstacle* o) {
    return aabb_intersect(&p->box, &o->box);
}

static void clear_obstacles(Scene* s) {
    free(s->obstacles);
    s->obstacles = NULL;
    s->obstacleCount = 0;
}

static void clear_coins(Scene* s) {
    free(s->coins);
    s->coins = NULL;
    s->coinCount = 0;
}

static float rand_float(float a, float b) {
    return a + ((float)rand() / RAND_MAX) * (b - a);
}

static void spawn_obstacle(Scene* s) {
    s->nextObstacleX += rand_float(20.0f, 25.0f);
    vec3 size;
    size.x = rand_float(s->player.box.size.x, s->player.box.size.x * 3.0f);
    size.y = rand_float(s->player.box.size.y, s->player.box.size.y * 2.0f);
    size.z = rand_float(s->player.box.size.z, s->player.box.size.z * 10.0f);
    vec3 pos;
    pos.x = s->nextObstacleX;
    pos.y = size.y * 0.5f;
    float hw = s->ground.halfWidth;
    pos.z = rand_float(-hw + size.z * 0.5f, hw - size.z * 0.5f);
    s->obstacleCount++;
    s->obstacles = realloc(s->obstacles, sizeof(Obstacle) * s->obstacleCount);
    init_obstacle(&s->obstacles[s->obstacleCount - 1], pos, size, s->player.score);
}

static void spawn_coin(Scene* s) {
    s->nextCoinX += rand_float(8.0f, 12.0f);
    vec3 pos;
    pos.x = s->nextCoinX;
    pos.y = s->player.box.size.y * 0.5f + 0.5f;
    float hw = s->ground.halfWidth;
    pos.z = rand_float(-hw + 0.6f, hw - 0.6f);
    s->coinCount++;
    s->coins = realloc(s->coins, sizeof(Coin) * s->coinCount);
    init_coin(&s->coins[s->coinCount - 1], pos);
}

void init_scene(Scene* s) {
    load_coin_model(ASSET_PATH("models" PATH_SEP "coin.obj"));
    srand((unsigned)time(NULL));
    float cube = 1.0f;
    float halfH = cube * 0.5f;
    init_player(&s->player, (vec3){0.0f, halfH, 0.0f}, cube, 8.0f, 100.0f, 0.5f);
    s->player.velocity.x = 5.0f;
    init_ground(&s->ground, cube * 20.0f, ASSET_PATH("textures" PATH_SEP "ground.bmp"));
    s->obstacles = NULL;
    s->obstacleCount = 0;
    s->nextObstacleX = s->player.box.position.x + 20.0f;
    while (s->nextObstacleX < s->player.box.position.x + INITIAL_OBSTACLE_REGION)
        spawn_obstacle(s);
    s->coins = NULL;
    s->coinCount = 0;
    s->nextCoinX = s->player.box.position.x + 8.0f;
    while (s->nextCoinX < s->player.box.position.x + INITIAL_OBSTACLE_REGION)
        spawn_coin(s);
    s->lost = false;
    s->lostTimer = 0.0;
}

void reset_scene(Scene* s) {
    float halfH = s->player.box.size.y * 0.5f;
    vec3 start = {0.0f, halfH, 0.0f};
    clear_obstacles(s);
    clear_coins(s);
    s->player.box.position = start;
    s->player.velocity = (vec3){5.0f, 0.0f, 0.0f};
    s->player.onGround = true;
    s->player.score = 0;
    s->player.coins = 0;
    s->nextObstacleX = start.x + 20.0f;
    while (s->nextObstacleX < start.x + INITIAL_OBSTACLE_REGION)
        spawn_obstacle(s);
    s->nextCoinX = start.x + 8.0f;
    while (s->nextCoinX < start.x + INITIAL_OBSTACLE_REGION)
        spawn_coin(s);
    s->lost = false;
    s->lostTimer = 0.0;
}

bool update_scene(Scene* s, double dt, float lateralInput) {
    if (s->lost) {
        s->lostTimer += dt;
        update_player(&s->player, dt, 0.0f);
        for (int i = 0; i < s->obstacleCount; ++i)
            update_obstacle(&s->obstacles[i], dt);
        if (s->lostTimer >= 2.0)
            return true;
    } else {
        update_player(&s->player, dt, lateralInput);
        for (int i = 0; i < s->obstacleCount; ++i)
            update_obstacle(&s->obstacles[i], dt);
        if (is_player_off_ground(&s->ground, &s->player)) {
            s->player.velocity.x = 0.0f;
            s->lost = true;
            s->lostTimer = 0.0f;
        } else {
            for (int i = 0; i < s->obstacleCount; ++i) {
                if (player_hits_obstacle(&s->player, &s->obstacles[i])) {
                    s->obstacles[i].velocity.x = s->player.velocity.x * 0.5f;
                    s->player.velocity.x = 0.0f;
                    s->lost = true;
                    s->lostTimer = 0.0f;
                    break;
                }
            }
        }
    }
    int wO = 0;
    for (int i = 0; i < s->obstacleCount; ++i) {
        if (s->obstacles[i].box.position.x >= s->player.box.position.x - 10.0f)
            s->obstacles[wO++] = s->obstacles[i];
    }
    s->obstacleCount = wO;
    s->obstacles = realloc(s->obstacles, sizeof(Obstacle) * s->obstacleCount);
    while (s->nextObstacleX < s->player.box.position.x + INITIAL_OBSTACLE_REGION)
        spawn_obstacle(s);
    for (int i = 0; i < s->coinCount; ++i)
        update_coin(&s->coins[i], dt);
    int wC = 0;
    for (int i = 0; i < s->coinCount; ++i) {
        bool remove = false;
        if (check_coin_collision(&s->coins[i], &s->player)) {
            s->player.coins++;
            remove = true;
        } else if (s->coins[i].position.x < s->player.box.position.x - 10.0f) {
            remove = true;
        }
        if (!remove)
            s->coins[wC++] = s->coins[i];
    }
    s->coinCount = wC;
    s->coins = realloc(s->coins, sizeof(Coin) * s->coinCount);
    while (s->nextCoinX < s->player.box.position.x + INITIAL_OBSTACLE_REGION)
        spawn_coin(s);
    s->player.score = (long)floorf(s->player.box.position.x);
    return false;
}

void render_scene(const Scene* s) {
    draw_skybox(globalCamera.position);
    draw_ground(&s->ground, s->player.box.position.x);
    for (int i = 0; i < s->coinCount; ++i)
        draw_coin(&s->coins[i]);
    for (int i = 0; i < s->obstacleCount; ++i)
        draw_obstacle(&s->obstacles[i]);
    draw_player(&s->player);
}