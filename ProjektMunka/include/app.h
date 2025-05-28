#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "control.h"
#include "camera.h"
#include "scene.h"
#include "menu.h"
#include "gameover.h"
#include "info.h"

#define BRIGHTNESS_DELTA 0.1f
#define BRIGHTNESS_MIN   0.0f
#define BRIGHTNESS_MAX   2.0f

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
    STATE_INFO
} AppState;

typedef struct App {
    SDL_Window*   window;
    SDL_GLContext gl_context;
    bool          quit;
    double        uptime;
    AppState      state;

    Camera   camera;
    Scene    scene;
    Menu     menu;
    GameOver gameover;
    Info     info;
    Control  control;
    float     brightness;
} App;

void init_app(App* app, int width, int height);
void handle_app_events(App* app, SDL_Event* e);
void update_app(App* app);
void render_app(App* app);
void destroy_app(App* app);

#endif