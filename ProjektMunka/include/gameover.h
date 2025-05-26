#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

/* Előtöltve: struct App deklaráció, hogy a header ne húzza be teljes app.h-t. */
struct App;

/* ------------------------------------------------------------------------- */
/*  GameOver – az összes, game-over képernyőhöz szükséges adat                */
/* ------------------------------------------------------------------------- */
typedef struct {
    SDL_Rect restartBtn;   /* “Restart” gomb téglalapja                       */
    SDL_Rect menuBtn;      /* “Main menu” gomb téglalapja                     */
    float    fade;         /* 0 → teljesen átlátszó, 1 → teljesen látható     */
} GameOver;

/* ------------------------------------------------------------------------- */
/*  Inicializálás ablakméret alapján                                          */
void init_gameover(GameOver* g,int winW,int winH);

/*  Eseménykezelő – csak akkor aktivál, ha fade már elérte az 1-et            */
bool gameover_handle_event(GameOver* g,struct App* app,const SDL_Event* e);

/*  Logikai frissítés: fokozatosan növeli a fade-et (dt másodperc alatt)      */
void update_gameover(GameOver* g,double dt);

/*  Kirajzolás: a fade mező alapján áttűnve jelenik meg                       */
void render_gameover(const GameOver* g,int winW,int winH,
                     long score,long coins);

#endif /* GAMEOVER_H */
