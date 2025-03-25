#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "circle.h"
#include "color.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_CIRCLE_COUNT 100
#define COLOR_COUNT 6

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Circle Drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Circle circles[MAX_CIRCLE_COUNT];
    int circleCount = 0;
    int creating = 0;
    Circle tempCircle;
    int dragging = 0;
    int draggedCircleIndex = -1;
    int dragOffsetX = 0, dragOffsetY = 0;
    int approximationMethod = 0;
    int segments = 50;
    double stepAngle = 0.125;
    double maxSegmentLength = 10.0;
    Color palette[COLOR_COUNT];
    palette[0] = createColor(255, 0, 0);
    palette[1] = createColor(0, 255, 0);
    palette[2] = createColor(0, 0, 255);
    palette[3] = createColor(255, 255, 0);
    palette[4] = createColor(255, 0, 255);
    palette[5] = createColor(0, 255, 255);
    int running = 1;
    int mouseX = 0, mouseY = 0;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x;
                    int y = event.button.y;
                    int found = 0;
                    for (int i = circleCount - 1; i >= 0; i--) {
                        if (is_point_inside_circle(&circles[i], x, y)) {
                            dragging = 1;
                            draggedCircleIndex = i;
                            dragOffsetX = x - (int)circles[i].x;
                            dragOffsetY = y - (int)circles[i].y;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        creating = 1;
                        tempCircle.x = x;
                        tempCircle.y = y;
                        tempCircle.radius = 0;
                        tempCircle.color = palette[circleCount % COLOR_COUNT];
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (dragging) {
                        dragging = 0;
                        draggedCircleIndex = -1;
                    }
                    if (creating) {
                        if (tempCircle.radius > 5) {
                            if (circleCount < MAX_CIRCLE_COUNT) {
                                circles[circleCount++] = tempCircle;
                            }
                        }
                        creating = 0;
                    }
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                if (dragging && draggedCircleIndex != -1) {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    circles[draggedCircleIndex].x = x - dragOffsetX;
                    circles[draggedCircleIndex].y = y - dragOffsetY;
                }
                if (creating) {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    double dx = x - tempCircle.x;
                    double dy = y - tempCircle.y;
                    tempCircle.radius = sqrt(dx * dx + dy * dy);
                }
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1) {
                    approximationMethod = 0;
                } else if (event.key.keysym.sym == SDLK_2) {
                    approximationMethod = 1;
                } else if (event.key.keysym.sym == SDLK_3) {
                    approximationMethod = 2;
                }
            }
        }
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < circleCount; i++) {
            switch(approximationMethod) {
                case 0:
                    draw_circle_outline_by_segments(renderer, &circles[i], segments);
                    break;
                case 1:
                    draw_circle_outline_by_angle(renderer, &circles[i], stepAngle);
                    break;
                case 2:
                    draw_circle_outline_by_max_segment(renderer, &circles[i], maxSegmentLength);
                    break;
            }
        }
        if (creating) {
            switch(approximationMethod) {
                case 0:
                    draw_circle_outline_by_segments(renderer, &tempCircle, segments);
                    break;
                case 1:
                    draw_circle_outline_by_angle(renderer, &tempCircle, stepAngle);
                    break;
                case 2:
                    draw_circle_outline_by_max_segment(renderer, &tempCircle, maxSegmentLength);
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < circleCount; i++) {
            if (is_point_inside_circle(&circles[i], mouseX, mouseY)) {
                int cx = (int)circles[i].x;
                int cy = (int)circles[i].y;
                int size = 10;
                SDL_RenderDrawLine(renderer, cx - size, cy, cx + size, cy);
                SDL_RenderDrawLine(renderer, cx, cy - size, cx, cy + size);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}