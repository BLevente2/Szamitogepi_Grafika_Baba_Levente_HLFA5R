#include "skybox.h"
#include <GL/gl.h>

static const float SZ = 500.0f;

static void sky_color(float t, float* r, float* g, float* b)
{
    const float hr = 0.529f, hg = 0.808f, hb = 0.922f;
    const float zr = 0.035f, zg = 0.329f, zb = 0.612f;
    *r = hr + (zr - hr) * t;
    *g = hg + (zg - hg) * t;
    *b = hb + (zb - hb) * t;
}

void draw_skybox(vec3 camPos)
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float r1, g1, b1, r2, g2, b2;
    sky_color(0.0f, &r1, &g1, &b1);
    sky_color(1.0f, &r2, &g2, &b2);

    glBegin(GL_QUADS);

    /* +Y */
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ,  SZ);
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ,  SZ);

    /* -Y */
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ,  SZ);
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ,  SZ);
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ, -SZ);
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ, -SZ);

    /* +Z */
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ,  SZ);
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ,  SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ,  SZ);
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ,  SZ);

    /* -Z */
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ, -SZ);
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ, -SZ);

    /* +X */
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ,  SZ);
    glColor3f(r1, g1, b1); glVertex3f( SZ, -SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ, -SZ);
    glColor3f(r2, g2, b2); glVertex3f( SZ,  SZ,  SZ);

    /* -X */
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ, -SZ);
    glColor3f(r1, g1, b1); glVertex3f(-SZ, -SZ,  SZ);
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ,  SZ);
    glColor3f(r2, g2, b2); glVertex3f(-SZ,  SZ, -SZ);

    glEnd();

    glPopMatrix();
    glPopAttrib();
}