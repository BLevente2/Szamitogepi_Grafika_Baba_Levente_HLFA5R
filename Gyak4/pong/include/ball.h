#ifndef BALL_H
#define BALL_H

typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
    float angle;
    float angular_speed;
} Ball;

void init_ball(Ball* ball, float x, float y);
void update_ball(Ball* ball, double time);
void render_ball(Ball* ball);

#endif