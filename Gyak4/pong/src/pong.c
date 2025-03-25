#include "pong.h"
#include "ball.h"
#include "pad.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <stdio.h>
#include <string.h>
static GLuint base = 0;
static void build_font(void)
{
    HFONT font;
    base = glGenLists(96);
    font = CreateFont(-16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Arial");
    HDC hDC = wglGetCurrentDC();
    SelectObject(hDC, font);
    wglUseFontBitmaps(hDC, 32, 96, base);
}
static void render_text(const char* text, float x, float y)
{
    if(base == 0)
        build_font();
    glRasterPos2f(x, y);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}
static void render_score(Pong* pong)
{
    char score_text[64];
    sprintf(score_text, "%d - %d", pong->score_left, pong->score_right);
    render_text(score_text, pong->width / 2 - 20, 30);
}
void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
    pong->score_left = 0;
    pong->score_right = 0;
}
void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}
void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
    render_score(pong);
}
void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}
void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}
void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}
void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}
void bounce_ball(Pong* pong)
{
    if(pong->ball.x - pong->ball.radius < 50){
        if(pong->ball.y >= pong->left_pad.y && pong->ball.y <= pong->left_pad.y + pong->left_pad.height){
            pong->ball.x = pong->ball.radius + 50;
            pong->ball.speed_x *= -1.05;
            pong->ball.angular_speed = -pong->ball.angular_speed;
        } else {
            pong->score_right++;
            init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
        }
    }
    if(pong->ball.x + pong->ball.radius > pong->width - 50){
        if(pong->ball.y >= pong->right_pad.y && pong->ball.y <= pong->right_pad.y + pong->right_pad.height){
            pong->ball.x = pong->width - pong->ball.radius - 50;
            pong->ball.speed_x *= -1.05;
            pong->ball.angular_speed = -pong->ball.angular_speed;
        } else {
            pong->score_left++;
            init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
        }
    }
    if(pong->ball.y - pong->ball.radius < 0){
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1.05;
        pong->ball.angular_speed = -pong->ball.angular_speed;
    }
    if(pong->ball.y + pong->ball.radius > pong->height){
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1.05;
        pong->ball.angular_speed = -pong->ball.angular_speed;
    }
}