#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Rect restartBtn;
    SDL_Rect menuBtn;
} GameOver;

struct App;

void init_gameover(GameOver* g, int winW, int winH);
bool gameover_handle_event(GameOver* g, struct App* app, const SDL_Event* e);
/**
 * Renders the Game Over screen.
 * @param g       Pointer to the GameOver data (button positions).
 * @param winW    Window width.
 * @param winH    Window height.
 * @param score   Final score to display.
 * @param coins   Number of collected coins to display.
 */
void render_gameover(const GameOver* g, int winW, int winH, long score, long coins);

#endif // GAMEOVER_H