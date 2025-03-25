#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "line.h"
#include "palette.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_LINE_COUNT 100

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Line Drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Palette palette = createPalette(10, 10, 50, 50, 10);
    Color currentColor = palette.colors[0];
    Line lines[MAX_LINE_COUNT];
    int lineCount = 0;
    int clickCount = 0;
    SDL_Point tempStart;
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int index = getPaletteColorIndex(palette, mouseX, mouseY);
                if (index != -1) {
                    currentColor = palette.colors[index];
                } else {
                    if (clickCount == 0) {
                        tempStart.x = mouseX;
                        tempStart.y = mouseY;
                        clickCount = 1;
                    } else {
                        if (lineCount < MAX_LINE_COUNT) {
                            SDL_Point end = {mouseX, mouseY};
                            lines[lineCount++] = createLine(tempStart, end, currentColor);
                        }
                        clickCount = 0;
                    }
                }
            }
        }
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        printf("Mouse Position: %d %d\n", mouseX, mouseY);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawPalette(renderer, palette);
        for (int i = 0; i < lineCount; i++) {
            drawLine(renderer, lines[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}