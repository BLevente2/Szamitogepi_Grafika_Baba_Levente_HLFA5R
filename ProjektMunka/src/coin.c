#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "coin.h"
#include "load.h"
#include "draw.h"
#include "transform.h"

static Model coinModel;
static bool coinModelLoaded = false;

void load_coin_model(const char* path) {
    if (!coinModelLoaded) {
        init_model(&coinModel);
        if (!load_model(&coinModel, path)) {
            fprintf(stderr, "Failed to load coin model: %s\n", path);
            exit(EXIT_FAILURE);
        }
        scale_model(&coinModel, 0.6, 0.6, 0.6);
        coinModelLoaded = true;
    }
}

void unload_coin_model(void) {
    if (coinModelLoaded) {
        free_model(&coinModel);
        coinModelLoaded = false;
    }
}

static float rf(float a, float b) {
    return a + ((float)rand() / RAND_MAX) * (b - a);
}

void init_coin(Coin* c, vec3 pos) {
    c->radius = 0.6f;
    c->thickness = 0.15f;
    c->position = pos;
    c->rotationY = rf(0.0f, 360.0f);
    c->bobPhase = 0.0f;
    c->baseY = pos.y;
    init_rectangular_prism(&c->hitbox,
        c->thickness,
        c->radius * 2.0f,
        c->radius * 2.0f,
        (Color){1.0f, 0.84f, 0.0f},
        pos);
}

void update_coin(Coin* c, double dt) {
    c->rotationY += 90.0f * (float)dt;
    if (c->rotationY >= 360.0f) c->rotationY -= 360.0f;
    c->bobPhase += 2.0f * (float)dt;
    c->position.y = c->baseY + sinf(c->bobPhase) * 0.1f;
    c->hitbox.position = c->position;
}

void draw_coin(const Coin* c) {
    glPushMatrix();
    glTranslatef(c->position.x, c->position.y, c->position.z);
    glRotatef(c->rotationY, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.84f, 0.0f);
    draw_triangles(&coinModel);
    glPopMatrix();
}

bool check_coin_collision(const Coin* c, const Player* p) {
    vec3 a = p->box.position, as = p->box.size;
    vec3 b = c->hitbox.position, bs = c->hitbox.size;
    return fabsf(a.x - b.x) * 2.0f < (as.x + bs.x) &&
           fabsf(a.z - b.z) * 2.0f < (as.z + bs.z);
}