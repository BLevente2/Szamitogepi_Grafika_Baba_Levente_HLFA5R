#include "ground.h"
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <math.h>

#ifndef GL_BGR
#define GL_BGR  0x80E0
#endif
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
/* ----------------------------------------------------- */

static void surface_formats(const SDL_Surface* s,
                            GLenum* internalFmt,
                            GLenum* pixelFmt)
{
    const int    bpp   = s->format->BytesPerPixel;
    const Uint32 rmask = s->format->Rmask;

    *internalFmt = (bpp == 4) ? GL_RGBA : GL_RGB;
    if (bpp == 4)
        *pixelFmt = (rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
    else
        *pixelFmt = (rmask == 0x000000ff) ? GL_RGB  : GL_BGR;
}

void init_ground(Ground* g, float width, const char* path)
{
    g->width     = width;
    g->halfWidth = width * 0.5f;

    /* egy ciklus hossza a világban (world unit / repeat) */
    const float tileSizeX = 4.0f;      /* 4 egységenként ismétlődik a fa-minta */
    g->repeatZ = 1.0f;                 /* keresztben (Z) egyszer megy végig   */

    SDL_Surface* surf = IMG_Load(path);
    if (!surf) return;

    GLenum ifmt, pfmt;
    surface_formats(surf, &ifmt, &pfmt);

    glGenTextures(1, &g->texture);
    glBindTexture(GL_TEXTURE_2D, g->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,   GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,   GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, ifmt,
                 surf->w, surf->h, 0,
                 pfmt, GL_UNSIGNED_BYTE, surf->pixels);

    SDL_FreeSurface(surf);

    /* X-irányú ismétlésszám egy 20 000 egység hosszú quadon */
    g->repeatX = (20000.0f / tileSizeX);
}

void draw_ground(const Ground* g, float playerX)
{
    const float length   = 20000.0f;   /* fél oldalanként 20 000 egység       */
    const float tileSize = 4.0f;       /* l. init_ground – ugyanaz az érték   */

    /* ------------------------------------------------------------------ */
    /* 1) Előkészítés                                                     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g->texture);

    /* a textúra ne kapjon plusz színezést, és ne is befolyásolja a többieket */
    GLint oldEnv;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &oldEnv);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glColor3f(1.0f, 1.0f, 1.0f);

    /* 2) Texture-mátrix eltolása – világ-rögzített mintázat               */
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
        /* negatív, mert a geometriát +playerX-szel toljuk el */
        float shift = -fmodf(playerX / tileSize, 1.0f);
        glTranslatef(shift, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    /* 3) Rajzolás                                                        */
    glPushMatrix();
        glTranslatef(playerX, 0.0f, 0.0f);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,       0.0f);        glVertex3f(-length, 0.0f, -g->halfWidth);
            glTexCoord2f(g->repeatX, 0.0f);        glVertex3f( length, 0.0f, -g->halfWidth);
            glTexCoord2f(g->repeatX, g->repeatZ);  glVertex3f( length, 0.0f,  g->halfWidth);
            glTexCoord2f(0.0f,       g->repeatZ);  glVertex3f(-length, 0.0f,  g->halfWidth);
        glEnd();
    glPopMatrix();

    /* 4) Visszaállítás                                                   */
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, oldEnv);
    glDisable(GL_TEXTURE_2D);
}

bool is_player_off_ground(const Ground* g, const Player* p)
{
    float z = p->box.position.z;
    return z < -g->halfWidth || z > g->halfWidth;
}