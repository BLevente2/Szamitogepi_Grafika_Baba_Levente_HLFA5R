#include "control.h"

void init_control(Control* c) {
    c->lateralAxis = 0.0f;
    c->escapePressed = false;
    c->brightnessDecrease = false;
    c->brightnessIncrease = false;
}

void control_handle_event(Control* c, const SDL_Event* e) {
    if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
        bool down = e->type == SDL_KEYDOWN;
        SDL_Keycode k = e->key.keysym.sym;
        if (k == SDLK_LEFT || k == SDLK_a)  c->lateralAxis = down ? -1.0f : 0.0f;
        if (k == SDLK_RIGHT || k == SDLK_d) c->lateralAxis = down ? 1.0f : 0.0f;
        if (k == SDLK_ESCAPE && down)     c->escapePressed = true;
        if (k == SDLK_q)                c->brightnessDecrease = down;
        if (k == SDLK_e)                c->brightnessIncrease = down;
    }
}

void control_update(Control* c, double dt) {
    (void)dt;
    c->escapePressed = false;
}