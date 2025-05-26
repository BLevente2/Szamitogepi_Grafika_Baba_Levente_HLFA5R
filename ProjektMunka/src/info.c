#include "info.h"
#include "app.h"
#include "font.h"
#include <GL/gl.h>
#include <string.h>

static void orthoOn(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

static void orthoOff(void) {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void drawQuad(const SDL_Rect* rect, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(rect->x, rect->y);
    glVertex2f(rect->x + rect->w, rect->y);
    glVertex2f(rect->x + rect->w, rect->y + rect->h);
    glVertex2f(rect->x, rect->y + rect->h);
    glEnd();
}

void init_info(Info* info, int width, int height) {
    info->backBtn = (SDL_Rect){ width - 200, height - 80, 180, 60 };
}

bool info_handle_event(Info* info, struct App* app, const SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
        SDL_Point point = { event->button.x, event->button.y };
        if (SDL_PointInRect(&point, &info->backBtn)) {
            app->state = STATE_MENU;
            return true;
        }
    }
    return false;
}

void render_info(const Info* info, int width, int height) {
    glDisable(GL_DEPTH_TEST);
    orthoOn(width, height);

    glColor3f(1.0f, 0.0f, 0.0f);
    render_text("About Cubestacle", width, height, 40, 60);

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
    int lineSpacing = 52;
    int y = 120;
    for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); ++i) {
        glColor3f(0.0f, 0.0f, 0.0f);
        render_text(lines[i], width, height, 40, (float)y);
        y += lineSpacing;
    }

    drawQuad(&info->backBtn, 0.8f, 0.8f, 0.8f);
    glColor3f(0.0f, 0.0f, 0.0f);
    const char* label = "Back";
    int textWidth = (int)strlen(label) * 24;
    float textX = info->backBtn.x + (info->backBtn.w - textWidth) * 0.5f;
    float textY = info->backBtn.y + (info->backBtn.h + 48) * 0.5f;
    render_text(label, width, height, textX, textY);

    orthoOff();
    glEnable(GL_DEPTH_TEST);
}