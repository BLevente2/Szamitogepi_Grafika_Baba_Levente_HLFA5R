#include "physics.h"

/* ------------------------------------------------ gravity ---------- */
void physics_apply_gravity(PhysicsBody* b, float g)
{
    if(!b->onGround)
        b->velocity.y += g;     /* g < 0 → lefele gyorsul */
}

/* ------------------------------------------------ integrate -------- */
void physics_integrate(PhysicsBody* b, double dt)
{
    b->position.x += b->velocity.x * (float)dt;
    b->position.y += b->velocity.y * (float)dt;
    b->position.z += b->velocity.z * (float)dt;

    /* egyszerű talaj-ütközés Y=0 síkon */
    if(b->position.y < 0.0f){
        b->position.y = 0.0f;
        b->velocity.y = 0.0f;
        b->onGround   = true;
    }
}

/* ------------------------------------------------ impulse ---------- */
void physics_transfer_impulse(PhysicsBody* a,
                              PhysicsBody* b,
                              float restitution)
{
    /* relatív sebesség csak X-ben */
    float rel = a->velocity.x - b->velocity.x;

    /* impulzus nagysága (egydimenziós rugó-ütközés) */
    float j = -(1.0f + restitution) * rel
              / (1.0f / a->mass + 1.0f / b->mass);

    a->velocity.x += j / a->mass;
    b->velocity.x -= j / b->mass;
}