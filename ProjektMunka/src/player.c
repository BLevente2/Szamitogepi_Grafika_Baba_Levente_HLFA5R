#include "player.h"

void init_player(Player* p,
    vec3    startPos,
    float   cubeSize,
    float   lateralSpeed,
    float   maxForwardSpeed,
    float   forwardAcceleration)
{
    Color red = { 1.0f, 0.0f, 0.0f };
    init_rectangular_prism(&p->box, cubeSize, cubeSize, cubeSize, red, startPos);
    p->velocity = (vec3){ 5.0f, 0.0f, 0.0f };
    p->mass = 1.0f;
    p->onGround = true;
    p->lateralSpeed = lateralSpeed;
    p->maxForwardSpeed = maxForwardSpeed;
    p->forwardAcceleration = forwardAcceleration;
    p->score = 0;
    p->coins = 0;
}

void update_player(Player* p, double dt, float lateralInput)
{
    p->velocity.x += p->forwardAcceleration * (float)dt;
    if (p->velocity.x > p->maxForwardSpeed)
        p->velocity.x = p->maxForwardSpeed;
    p->velocity.z = lateralInput * p->lateralSpeed;
    if (!p->onGround)
        p->velocity.y -= 9.81f * (float)dt;

    p->box.position.x += p->velocity.x * (float)dt;
    p->box.position.y += p->velocity.y * (float)dt;
    p->box.position.z += p->velocity.z * (float)dt;

    float floorY = p->box.size.y * 0.5f;
    if (p->box.position.y < floorY) {
        p->box.position.y = floorY;
        p->velocity.y = 0.0f;
        p->onGround = true;
    }
    else {
        p->onGround = false;
    }
}

void draw_player(const Player* p)
{
    draw_rectangular_prism(&p->box);
}