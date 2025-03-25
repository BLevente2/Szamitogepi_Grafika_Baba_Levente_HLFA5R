#include "cylinder.h"
#include <GL/gl.h>
#include <math.h>

void init_cylinder(){
}

void cylinder_draw(){
    int slices = 10;
    float radius = 0.2f;
    float height = 0.5f;
    int i;
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= slices; i++){
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, y, 0);
        glVertex3f(x, y, height);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    for(i = 0; i <= slices; i++){
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, y, 0);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,height);
    for(i = 0; i <= slices; i++){
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, y, height);
    }
    glEnd();
}