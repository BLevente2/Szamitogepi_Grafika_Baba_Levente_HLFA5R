#include "menu.h"
#include "app.h"
#include "rectangular_prism.h"
#include <GL/gl.h>
#include <GL/glu.h>

/* ------------------------------------------------ helpers */
static void ortho2D(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

static void ortho2D_pop(void) {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void draw_quad(const SDL_Rect* r, float rCol, float gCol, float bCol) {
    glColor3f(rCol, gCol, bCol);
    glBegin(GL_QUADS);
    glVertex2f(r->x,        r->y);
    glVertex2f(r->x + r->w, r->y);
    glVertex2f(r->x + r->w, r->y + r->h);
    glVertex2f(r->x,        r->y + r->h);
    glEnd();
}

/* ------------------------------------------------ public */
void init_menu(Menu* m, int w, int h) {
    int bw = 240, bh = 64;
    m->startBtn = (SDL_Rect){ (w - bw) / 2, h / 2 + 80,  bw, bh };
    m->quitBtn  = (SDL_Rect){ (w - bw) / 2, h / 2 + 160, bw, bh };
    m->infoBtn  = (SDL_Rect){ w - 180,         20,       160, 48 };
    m->cubeAngle = 0.0f;
}

void update_menu(Menu* m, double dt) {
    m->cubeAngle += 30.0f * dt;
    if (m->cubeAngle >= 360.0f) m->cubeAngle -= 360.0f;
}

bool menu_handle_event(Menu* m, struct App* app, const SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        SDL_Point p = { e->button.x, e->button.y };
        if (SDL_PointInRect(&p, &m->startBtn)) {
            reset_scene(&app->scene);
            app->state = STATE_PLAYING;
            return true;
        }
        if (SDL_PointInRect(&p, &m->infoBtn)) {
            app->state = STATE_INFO;
            return true;
        }
        if (SDL_PointInRect(&p, &m->quitBtn)) {
            app->quit = true;
            return true;
        }
    }
    return false;
}

void render_menu(const Menu* m, int w, int h) {
    /* 3D cube logo */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, 1.2f, -8.0f);
    glRotatef(m->cubeAngle, 0.0f, 1.0f, 0.0f);

    RectangularPrism cube;
    init_rectangular_prism(&cube, 1.8f, 1.8f, 1.8f,
                           (Color){1.0f, 0.0f, 0.0f},
                           (vec3){0, 0, 0});
    draw_rectangular_prism(&cube);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    /* 2D UI */
    glDisable(GL_DEPTH_TEST);
    ortho2D(w, h);

    glColor3f(1.0f, 0.0f, 0.0f);
    render_text("Cubestacle", w, h, w/2 - 120, 60);

    draw_quad(&m->startBtn, 0.8f, 0.8f, 0.8f);
    draw_quad(&m->infoBtn,  0.8f, 0.8f, 0.8f);
    draw_quad(&m->quitBtn,  0.8f, 0.8f, 0.8f);

    glColor3f(0.0f, 0.0f, 0.0f);
    render_text("Start", w, h, m->startBtn.x + 70, m->startBtn.y + 22);
    render_text("Info",  w, h, m->infoBtn.x  + 55, m->infoBtn.y  + 15);
    render_text("Quit",  w, h, m->quitBtn.x  + 80, m->quitBtn.y  + 22);

    ortho2D_pop();
    glEnable(GL_DEPTH_TEST);
}