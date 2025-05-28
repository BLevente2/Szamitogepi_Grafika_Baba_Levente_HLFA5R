#include "app.h"
#include "font.h"
#include "control.h"
#include "coin.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static const GLfloat baseFogColor[3] = { 0.529f, 0.808f, 0.922f };

static void draw_score(const App* app);

static void init_opengl(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    init_opengl(w, h);
}

void init_app(App* app, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    app->window = SDL_CreateWindow(
        "CubestacleSDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED
    );
    app->gl_context = SDL_GL_CreateContext(app->window);
    SDL_MaximizeWindow(app->window);

    int w, h;
    SDL_GetWindowSize(app->window, &w, &h);
    reshape(w, h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    const GLfloat fogC[4] = { baseFogColor[0], baseFogColor[1], baseFogColor[2], 1.0f };
    glFogfv(GL_FOG_COLOR, fogC);
    glFogf(GL_FOG_START, 20.0f);
    glFogf(GL_FOG_END, 100.0f);
    glClearColor(fogC[0], fogC[1], fogC[2], 1.0f);

    app->quit = false;
    app->state = STATE_MENU;

    init_camera(&app->camera);
    init_scene(&app->scene);
    init_menu(&app->menu, w, h);
    init_gameover(&app->gameover, w, h);
    init_info(&app->info, w, h);
    init_control(&app->control);

    app->uptime = SDL_GetTicks() / 1000.0;
    app->brightness = 1.0f;
}

void handle_app_events(App* app, SDL_Event* e) {
    if (e->type == SDL_QUIT) {
        app->quit = true;
        return;
    }

    if (app->state == STATE_PLAYING)
        control_handle_event(&app->control, e);

    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED) {
        reshape(e->window.data1, e->window.data2);
        init_menu(&app->menu, e->window.data1, e->window.data2);
        init_gameover(&app->gameover, e->window.data1, e->window.data2);
        init_info(&app->info, e->window.data1, e->window.data2);
    }

    if (app->state == STATE_PLAYING && e->type == SDL_MOUSEWHEEL) {
        adjust_camera_radius(e->wheel.y * 1.0f);
    }

    if (app->state == STATE_MENU) {
        menu_handle_event(&app->menu, app, e);
    }
    else if (app->state == STATE_INFO) {
        info_handle_event(&app->info, app, e);
    }
    else if (app->state == STATE_GAMEOVER) {
        gameover_handle_event(&app->gameover, app, e);
    }
    else if (app->state == STATE_PLAYING && e->type == SDL_KEYDOWN) {
        if (app->control.brightnessDecrease) {
            app->brightness -= BRIGHTNESS_DELTA;
            if (app->brightness < BRIGHTNESS_MIN) app->brightness = BRIGHTNESS_MIN;
        }
        else if (app->control.brightnessIncrease) {
            app->brightness += BRIGHTNESS_DELTA;
            if (app->brightness > BRIGHTNESS_MAX) app->brightness = BRIGHTNESS_MAX;
        }
        else {
            SDL_Keycode k = e->key.keysym.sym;
            if (k == SDLK_ESCAPE) app->state = STATE_MENU;
            else if (k == SDLK_w || k == SDLK_UP) adjust_camera_angle(+0.05f);
            else if (k == SDLK_s || k == SDLK_DOWN) adjust_camera_angle(-0.05f);
            else if (k == SDLK_PLUS || k == SDLK_KP_PLUS) adjust_camera_radius(+1.0f);
            else if (k == SDLK_MINUS || k == SDLK_KP_MINUS) adjust_camera_radius(-1.0f);
        }
    }
}

void update_app(App* app) {
    double now = SDL_GetTicks() / 1000.0;
    double dt = now - app->uptime;
    app->uptime = now;

    if (app->state == STATE_MENU) {
        update_menu(&app->menu, dt);
        return;
    }
    if (app->state == STATE_GAMEOVER) {
        update_gameover(&app->gameover, dt);
        return;
    }
    if (app->state != STATE_PLAYING) return;

    update_camera(&app->camera, app->scene.player.box.position);
    control_update(&app->control, dt);

    if (update_scene(&app->scene, dt, app->control.lateralAxis)) {
        app->state = STATE_GAMEOVER;
    }
}

void render_app(App* app) {
    GLfloat fogC[4] = {
        baseFogColor[0] * app->brightness,
        baseFogColor[1] * app->brightness,
        baseFogColor[2] * app->brightness,
        1.0f
    };
    glClearColor(fogC[0], fogC[1], fogC[2], 1.0f);
    glFogfv(GL_FOG_COLOR, fogC);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    apply_camera();

    int w, h;
    SDL_GetWindowSize(app->window, &w, &h);

    if (app->state == STATE_PLAYING) {
        render_scene(&app->scene);
        draw_score(app);
    }
    else if (app->state == STATE_MENU) {
        render_menu(&app->menu, w, h);
    }
    else if (app->state == STATE_INFO) {
        render_info(&app->info, w, h);
    }
    else if (app->state == STATE_GAMEOVER) {
        render_gameover(
            &app->gameover,
            w, h,
            app->scene.player.score,
            app->scene.player.coins
        );
    }

    SDL_GL_SwapWindow(app->window);
}

static void draw_score(const App* app) {
    int w, h;
    SDL_GetWindowSize(app->window, &w, &h);

    char scoreBuf[32];
    sprintf(scoreBuf, "%ld", app->scene.player.score);
    int textW = (int)strlen(scoreBuf) * 24;

    GLboolean depthWas = glIsEnabled(GL_DEPTH_TEST);
    if (depthWas) glDisable(GL_DEPTH_TEST);

    glColor3f(0.0f, 0.0f, 0.0f);
    render_text(scoreBuf, w, h, (w - textW) * 0.5f, 50.0f);

    char coinBuf[32];
    sprintf(coinBuf, "Coins: %ld", app->scene.player.coins);
    int coinTextW = (int)strlen(coinBuf) * 24;
    glColor3f(0.83f, 0.66f, 0.0f);
    render_text(coinBuf, w, h, w - coinTextW - 40, 50.0f);

    if (depthWas) glEnable(GL_DEPTH_TEST);
}

void destroy_app(App* app) {
    if (app->gl_context) SDL_GL_DeleteContext(app->gl_context);
    if (app->window) SDL_DestroyWindow(app->window);
    unload_coin_model();
    IMG_Quit();
    SDL_Quit();
}