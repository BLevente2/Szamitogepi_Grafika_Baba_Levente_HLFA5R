#include "rectangular_prism.h"
#include <GL/gl.h>

void init_rectangular_prism(RectangularPrism* p,
                            float w,float h,float d,
                            Color c,vec3 pos)
{
    p->size      = (vec3){w,h,d};
    p->color     = c;
    p->position  = pos;
    p->rotationY = 0.0f;
}

void set_rectangular_prism_size(RectangularPrism* p,float w,float h,float d)
{
    p->size = (vec3){w,h,d};
}

void set_rectangular_prism_color(RectangularPrism* p,Color c)
{
    p->color = c;
}

void set_rectangular_prism_rotation(RectangularPrism* p,float rot)
{
    p->rotationY = rot;
}

void draw_rectangular_prism(const RectangularPrism* p)
{
    glPushMatrix();
    glTranslatef(p->position.x,p->position.y,p->position.z);
    glRotatef(p->rotationY,0.0f,1.0f,0.0f);
    glScalef(p->size.x,p->size.y,p->size.z);
    glColor3f(p->color.red,p->color.green,p->color.blue);
    glBegin(GL_QUADS);
        glVertex3f(-0.5f,-0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f,-0.5f,-0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);
        glVertex3f( 0.5f,-0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glEnd();
    glPopMatrix();
}