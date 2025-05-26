#ifndef CONTROL_H
#define CONTROL_H
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct{
    float lateralAxis;
    bool  escapePressed;
} Control;

void init_control(Control* c);
void control_handle_event(Control* c,const SDL_Event* e);
void control_update(Control* c,double dt);
#endif
