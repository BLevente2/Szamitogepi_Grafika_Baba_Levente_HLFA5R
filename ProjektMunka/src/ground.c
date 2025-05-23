#include "ground.h"
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif

#define STRIP_COUNT 32

static GLuint load_texture(const char* path, int* wOut, int* hOut)
{
    SDL_Surface* surf = IMG_Load(path);
    if (!surf) return 0;

    SDL_Surface* bgra = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_BGRA8888, 0);
    SDL_FreeSurface(surf);
    if (!bgra) return 0;
    surf = bgra;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, surf->w, surf->h, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, surf->pixels);

    GLenum err = glGetError();
    if (err) fprintf(stderr, "ground tex load error 0x%X\n", err);

    *wOut = surf->w;
    *hOut = surf->h;
    SDL_FreeSurface(surf);
    return tex;
}

void init_ground(Ground* g, float width, const char* path)
{
    g->width     = width;
    g->halfWidth = width * 0.5f;

    const float tileSizeX = 4.0f;
    g->repeatZ = 1.0f;

    int tw, th;
    g->texture = load_texture(path, &tw, &th);
    if (!g->texture) return;

    g->repeatX = 20000.0f / tileSizeX;
}

static void draw_strip(float x0, float x1, float s0, float s1,
                       float halfW, float repeatZ)
{
    glBegin(GL_QUADS);
    glTexCoord2f(s0, 0.0f);       glVertex3f(x0, 0.0f, -halfW);
    glTexCoord2f(s1, 0.0f);       glVertex3f(x1, 0.0f, -halfW);
    glTexCoord2f(s1, repeatZ);    glVertex3f(x1, 0.0f,  halfW);
    glTexCoord2f(s0, repeatZ);    glVertex3f(x0, 0.0f,  halfW);
    glEnd();
}

void draw_ground(const Ground* g, float playerX)
{
    const float length   = 20000.0f;
    const float tileSize = 4.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g->texture);

    GLint oldEnv;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &oldEnv);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(playerX, 0.0f, 0.0f);

    float step   = (2.0f * length) / STRIP_COUNT;
    float sStep  = g->repeatX / STRIP_COUNT;
    float startX = -length;
    float startS = -fmodf(playerX / tileSize, 1.0f) * g->repeatX;

    for (int i = 0; i < STRIP_COUNT; ++i)
    {
        float x0 = startX + i * step;
        float x1 = x0 + step;
        float s0 = startS + i * sStep;
        float s1 = s0   + sStep;
        draw_strip(x0, x1, s0, s1, g->halfWidth, g->repeatZ);
    }

    glPopMatrix();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, oldEnv);
    glDisable(GL_TEXTURE_2D);
}

bool is_player_off_ground(const Ground* g, const Player* p)
{
    float z = p->box.position.z;
    return z < -g->halfWidth || z > g->halfWidth;
}
