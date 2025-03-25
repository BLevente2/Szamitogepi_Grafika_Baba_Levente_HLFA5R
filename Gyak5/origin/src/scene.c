#include "scene.h"
#include <GL/gl.h>
#include "sphere.h"
#include "cylinder.h"
#include "cone.h"

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
    sphere_update();
}

void render_scene(const Scene* scene)
{
    draw_origin();
    int i, j;
    float squareSize = 1.0f / 8.0f;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if((i + j) % 2 == 0)
                glColor3f(1,1,1);
            else
                glColor3f(0,0,0);
            glBegin(GL_QUADS);
            glVertex3f(i * squareSize, j * squareSize, 0);
            glVertex3f((i+1)*squareSize, j * squareSize, 0);
            glVertex3f((i+1)*squareSize, (j+1)*squareSize, 0);
            glVertex3f(i * squareSize, (j+1)*squareSize, 0);
            glEnd();
        }
    }
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0);
    glVertex3f(0.2, 0.2, 0.5);
    glColor3f(0,1,1);
    glVertex3f(0.8, 0.2, 0.5);
    glColor3f(1,0,1);
    glVertex3f(0.5, 0.8, 0.5);
    glEnd();
    glPushMatrix();
    glTranslatef(0.75, 0.75, 0.75);
    sphere_draw();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.75, 0.25, 0.25);
    cylinder_draw();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25, 0.75, 0.25);
    cone_draw();
    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
}