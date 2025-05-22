#include "info.h"
#include "app.h"
#include <GL/gl.h>

static void ortho_on(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

static void ortho_off(void) {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void quad(const SDL_Rect* r, float rCol, float gCol, float bCol) {
    glColor3f(rCol, gCol, bCol);
    glBegin(GL_QUADS);
        glVertex2f(r->x,          r->y);
        glVertex2f(r->x + r->w,   r->y);
        glVertex2f(r->x + r->w,   r->y + r->h);
        glVertex2f(r->x,          r->y + r->h);
    glEnd();
}

void init_info(Info* i, int w, int h) {
    /* Back gomb: 20-px margó a jobb és az alsó szélétől */
    i->backBtn = (SDL_Rect){ w - 200, h - 80, 180, 60 };
}

bool info_handle_event(Info* i, struct App* app, const SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        SDL_Point p = { e->button.x, e->button.y };
        if (SDL_PointInRect(&p, &i->backBtn)) {
            app->state = STATE_MENU;
            return true;
        }
    }
    return false;
}

void render_info(const Info* i, int w, int h) {
    glDisable(GL_DEPTH_TEST);
    ortho_on(w, h);

    /* ----------- title ------------ */
    glColor3f(1.0f, 0.0f, 0.0f);
    render_text("About Cubestacle", w, h, 40, 60);

    /* ----------- body ------------- */
    const char* lines[] = {
        "Welcome to Cubestacle – an endless 3-D runner where a brave red",
        "cube dashes forward over an infinite ground. Your aim is simple:",
        "stay alive as long as you can while your score rises with every",
        "metre travelled.",
        "",
        "Controls:",
        "   LEFT / A       – move left",
        "   RIGHT / D      – move right",
        "   Mouse wheel    – zoom camera",
        "   W / UP         – tilt camera up",
        "   S / DOWN       – tilt camera down",
        "   ESC            – back to menu",
        "",
        "The cube accelerates steadily until it reaches its top speed.",
        "Touching any obstacle or falling off the track ends the run.",
        "",
        "Good luck and have fun!"
    };

    const int lineSpacing = 52;          /* 48-px font + 4-px leading */
    int y = 120;
    for (size_t k = 0; k < sizeof(lines) / sizeof(lines[0]); ++k, y += lineSpacing) {
        glColor3f(0.0f, 0.0f, 0.0f);
        render_text(lines[k], w, h, 40, (float)y);
    }

    /* ----------- back button ------ */
    quad(&i->backBtn, 0.8f, 0.8f, 0.8f);
    glColor3f(0.0f, 0.0f, 0.0f);
    render_text("Back", w, h,
                i->backBtn.x + 60,        /* kb. középre a 180-px széles gombon */
                i->backBtn.y + 20);

    ortho_off();
    glEnable(GL_DEPTH_TEST);
}