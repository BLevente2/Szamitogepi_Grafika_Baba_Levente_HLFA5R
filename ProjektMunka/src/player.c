#include "player.h"
#include <SDL2/SDL.h>

void init_player(Player* p,
                 vec3    startPos,
                 float   cubeSize,
                 float   lateralSpeed,
                 float   maxForwardSpeed,
                 float   forwardAcceleration)
{
    Color red = {1.0f, 0.0f, 0.0f};
    init_rectangular_prism(&p->box, cubeSize, cubeSize, cubeSize, red, startPos);
    p->score               = 0;
    p->lateralSpeed        = lateralSpeed;
    p->forwardSpeed        = 0.0f;
    p->maxForwardSpeed     = maxForwardSpeed;
    p->forwardAcceleration = forwardAcceleration;
}

void update_player(Player* p, double dt)
{
    p->forwardSpeed += p->forwardAcceleration * (float)dt;
    if (p->forwardSpeed > p->maxForwardSpeed)
        p->forwardSpeed = p->maxForwardSpeed;
    p->box.position.x += p->forwardSpeed * (float)dt;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float delta = p->lateralSpeed * (float)dt;
    if (keys[SDL_SCANCODE_LEFT]  || keys[SDL_SCANCODE_A])
        p->box.position.z -= delta;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
        p->box.position.z += delta;
}

void draw_player(const Player* p)
{
    draw_rectangular_prism(&p->box);
}