#include "ball.h"
#include <GL/gl.h>
#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 100;
    ball->speed_y = 100;
    ball->angle = 0;
    ball->angular_speed = 45;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->angle += ball->angular_speed * time;
    if(ball->angle >= 360)
        ball->angle -= 360;
    if(ball->angle < 0)
        ball->angle += 360;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;
    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->angle, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();
}