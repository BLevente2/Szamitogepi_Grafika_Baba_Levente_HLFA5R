#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdbool.h>
#include "types.h"          /* a vec3 definíciója itt van */

/* ------------------------------------------------------------------ */
/* Egyszerű fizikai test adatszerkezete                               */
typedef struct {
    vec3  position;         /* pozíció (m)          */
    vec3  velocity;         /* sebesség (m/s)       */
    float mass;             /* tömeg   (kg)         */
    bool  onGround;         /* áll-e épp talajon?   */
} PhysicsBody;
/* ------------------------------------------------------------------ */

/* Gravitációs gyorsulás alkalmazása                                   */
void physics_apply_gravity(PhysicsBody* b, float g);

/* Sima Euler-integrál a test mozgatására                               */
void physics_integrate(PhysicsBody* b, double dt);

/* Rugalmas ütközési impulzus két testen (csak X irány)                */
void physics_transfer_impulse(PhysicsBody* a,
                               PhysicsBody* b,
                               float restitution);

#endif /* PHYSICS_H */