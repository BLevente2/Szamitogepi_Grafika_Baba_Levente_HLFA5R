#ifndef INFO_H
#define INFO_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct App App;

typedef struct {
    SDL_Rect backBtn;
} Info;

void init_info(Info* i,int w,int h);
bool info_handle_event(Info* i,struct App* app,const SDL_Event* e);
void render_info(const Info* i,int w,int h);

#endif