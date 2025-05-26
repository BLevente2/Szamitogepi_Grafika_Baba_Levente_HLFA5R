#include "gameover.h"
#include "app.h"
#include "font.h"
#include "control.h"

#include <stdio.h>
#include <string.h>
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

static void draw_quad(const SDL_Rect* r, float grey, float alpha) {
    glColor4f(grey, grey, grey, alpha);
    glBegin(GL_QUADS);
    glVertex2f(r->x,       r->y);
    glVertex2f(r->x + r->w, r->y);
    glVertex2f(r->x + r->w, r->y + r->h);
    glVertex2f(r->x,       r->y + r->h);
    glEnd();
}

void init_gameover(GameOver* g, int w, int h) {
    const int bw = 260, bh = 64;
    g->restartBtn = (SDL_Rect){ (w - bw) / 2, h / 2 + 80, bw, bh };
    g->menuBtn    = (SDL_Rect){ (w - bw) / 2, h / 2 + 160, bw, bh };
    g->fade       = 0.0f;
}

bool gameover_handle_event(GameOver* g, struct App* a, const SDL_Event* e) {
    if (g->fade < 1.0f) return false;
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        SDL_Point p = { e->button.x, e->button.y };
        if (SDL_PointInRect(&p, &g->restartBtn)) {
            reset_scene(&a->scene);
            init_control(&a->control);
            a->state = STATE_PLAYING;
            return true;
        }
        if (SDL_PointInRect(&p, &g->menuBtn)) {
            a->state = STATE_MENU;
            return true;
        }
    }
    return false;
}

void update_gameover(GameOver* g, double dt) {
    g->fade += (float)(dt * 0.5);
    if (g->fade > 1.0f) g->fade = 1.0f;
}

void render_gameover(const GameOver* g, int w, int h, long score, long coins) {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ortho2D(w, h);

    float a = g->fade;

    glColor4f(1.0f, 0.0f, 0.0f, a);
    render_text("Game Over!", w, h, w / 2 - 110, 120);

    char buf[64];
    sprintf(buf, "Score: %ld", score);
    glColor4f(0.0f, 0.45f, 0.0f, a);
    render_text(buf, w, h, w / 2 - 90, 200);

    sprintf(buf, "Coins: %ld", coins);
    glColor4f(0.83f, 0.66f, 0.0f, a);
    render_text(buf, w, h, w / 2 - 90, 260);

    draw_quad(&g->restartBtn, 0.8f, a);
    draw_quad(&g->menuBtn,    0.8f, a);

    glColor4f(0.0f, 0.0f, 0.0f, a);
    {
        const char* label = "Restart";
        int textW = (int)strlen(label) * 24;
        float textX = g->restartBtn.x + (g->restartBtn.w - textW) * 0.5f;
        float textY = g->restartBtn.y + (g->restartBtn.h + 48) * 0.5f;
        render_text(label, w, h, textX, textY);
    }
    {
        const char* label = "Main Menu";
        int textW = (int)strlen(label) * 24;
        float baseX = g->menuBtn.x + (g->menuBtn.w - textW) * 0.5f;
        float textX = baseX - 8.0f;
        if (textX < g->menuBtn.x) textX = g->menuBtn.x;
        float textY = g->menuBtn.y + (g->menuBtn.h + 48) * 0.5f;
        render_text(label, w, h, textX, textY);
    }

    pop2D();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}