#include "gameover.h"
#include "app.h"
#include <stdio.h>      /* sprintf */
#include <GL/gl.h>

static void ortho2D(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

static void pop2D(void) {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void quad(const SDL_Rect* r, float rCol, float gCol, float bCol) {
    glColor3f(rCol, gCol, bCol);
    glBegin(GL_QUADS);
        glVertex2f(r->x         , r->y);
        glVertex2f(r->x + r->w  , r->y);
        glVertex2f(r->x + r->w  , r->y + r->h);
        glVertex2f(r->x         , r->y + r->h);
    glEnd();
}

void init_gameover(GameOver* g, int w, int h) {
    int bw = 260, bh = 64;
    g->restartBtn = (SDL_Rect){ (w - bw) / 2, h / 2 + 80 , bw, bh };
    g->menuBtn    = (SDL_Rect){ (w - bw) / 2, h / 2 + 160, bw, bh };
}

bool gameover_handle_event(GameOver* g, struct App* app,
                           const SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        SDL_Point p = { e->button.x, e->button.y };
        if (SDL_PointInRect(&p, &g->restartBtn)) {
            reset_scene(&app->scene);
            app->state = STATE_PLAYING;
            return true;
        }
        if (SDL_PointInRect(&p, &g->menuBtn)) {
            app->state = STATE_MENU;
            return true;
        }
    }
    return false;
}

void render_gameover(const GameOver* g, int w, int h, long score) {
    glDisable(GL_DEPTH_TEST);
    ortho2D(w, h);

    /* cím */
    glColor3f(1.0f, 0.0f, 0.0f);
    render_text("Game Over!", w, h, w / 2 - 110, 120);

    /* SCORE – erős sötétzölddel */
    char buf[64];
    sprintf(buf, "Score: %ld", score);
    glColor3f(0.0f, 0.45f, 0.0f);             /* sötétzöld */
    render_text(buf, w, h, w / 2 - 90, 200);

    /* gombok */
    quad(&g->restartBtn, 0.8f, 0.8f, 0.8f);
    quad(&g->menuBtn   , 0.8f, 0.8f, 0.8f);

    glColor3f(0.0f, 0.0f, 0.0f);
    render_text("Restart",   w, h,
                g->restartBtn.x + 60, g->restartBtn.y + 22);
    render_text("Main Menu", w, h,
                g->menuBtn.x    + 40, g->menuBtn.y    + 22);

    pop2D();
    glEnable(GL_DEPTH_TEST);
}