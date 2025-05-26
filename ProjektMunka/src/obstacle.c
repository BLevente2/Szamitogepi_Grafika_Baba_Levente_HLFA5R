#include "obstacle.h"
#include <stdlib.h>
#include <math.h>

static float randf(float a, float b){
    return a + ((float)rand() / (float)RAND_MAX) * (b - a);
}

static Color color_from_score(long score){
    const Color colors[] = {
        {0.0f, 0.0f, 1.0f},
        {0.5f, 0.0f, 0.5f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.4f, 0.7f},
        {0.0f, 1.0f, 0.0f}
    };
    int idx = (score / 150) % (sizeof(colors) / sizeof(colors[0]));
    return colors[idx];
}

void init_obstacle(Obstacle* o, vec3 pos, vec3 size, long score){
    Color c = color_from_score(score);
    init_rectangular_prism(&o->box, size.x, size.y, size.z, c, pos);
    set_rectangular_prism_rotation(&o->box, randf(-15.0f, 15.0f));
    o->velocity = (vec3){0.0f, 0.0f, 0.0f};
    o->mass     = 2.0f;
}

void update_obstacle(Obstacle* o, double dt){
    float floorY = o->box.size.y * 0.5f;

    if (o->box.position.y > floorY)
        o->velocity.y -= 9.81f * (float)dt;

    o->box.position.x += o->velocity.x * (float)dt;
    o->box.position.y += o->velocity.y * (float)dt;
    o->box.position.z += o->velocity.z * (float)dt;

    if (o->box.position.y < floorY){
        o->box.position.y = floorY;
        o->velocity.y     = 0.0f;
    }
}

void draw_obstacle(const Obstacle* o){
    draw_rectangular_prism(&o->box);
}

bool check_obstacle_collision(const Obstacle* o, const Player* p){
    vec3 aPos = p->box.position, aSize = p->box.size;
    vec3 bPos = o->box.position, bSize = o->box.size;

    return (fabsf(aPos.x - bPos.x) * 2.0f < (aSize.x + bSize.x)) &&
           (fabsf(aPos.y - bPos.y) * 2.0f < (aSize.y + bSize.y)) &&
           (fabsf(aPos.z - bPos.z) * 2.0f < (aSize.z + bSize.z));
}