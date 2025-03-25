#ifndef PONG_H
#define PONG_H

#include "ball.h"
#include "pad.h"
#include <stdbool.h>

typedef struct Pong
{
    int width;
    int height;
    Ball ball;
    Pad left_pad;
    Pad right_pad;
    int score_left;
    int score_right;
} Pong;

void init_pong(Pong* pong, int width, int height);
void update_pong(Pong* pong, double time);
void render_pong(Pong* pong);
void set_left_pad_position(Pong* pong, float position);
void set_left_pad_speed(Pong* pong, float speed);
void set_right_pad_position(Pong* pong, float position);
void set_right_pad_speed(Pong* pong, float speed);
void bounce_ball(Pong* pong);

#endif