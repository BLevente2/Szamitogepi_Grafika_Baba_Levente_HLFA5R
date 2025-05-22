#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct App App;          /* előre-deklaráció */

typedef struct {
    SDL_Rect startBtn;
    SDL_Rect quitBtn;
    SDL_Rect infoBtn;
    float    cubeAngle;
} Menu;

void init_menu(Menu* m,int w,int h);
void update_menu(Menu* m,double dt);
bool menu_handle_event(Menu* m,struct App* app,const SDL_Event* e);
void render_menu(const Menu* m,int w,int h);

#endif