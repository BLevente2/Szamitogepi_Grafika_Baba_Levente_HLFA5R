#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "camera.h"
#include "scene.h"
#include "menu.h"
#include "gameover.h"
#include "info.h"

/* A programban már nincs fényerő-kezelés (gBrightness, adjust_brightness),
   ezért sem külön header-, sem extern deklaráció nem szerepel itt. */

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
    AppState      state;
    Camera        camera;
    Scene         scene;
    Menu          menu;
    GameOver      gameover;
    Info          info;
    double        uptime;
} App;

/* Alap életciklus-függvények */
void init_app(App* app, int width, int height);
void handle_app_events(App* app, SDL_Event* e);
void update_app(App* app);
void render_app(App* app);
void destroy_app(App* app);

/* Segédfüggvények */
void draw_score(const App* app);
void render_text(const char* text, int x, int y, float r, float g);

#endif /* APP_H */
