#include "font.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>

static GLuint fontBase=0;

static void build_font(void){
#ifdef _WIN32
    HDC hdc=wglGetCurrentDC();
    fontBase=glGenLists(96);
    HFONT f=CreateFontA(-48,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,"Arial");
    HGDIOBJ old=SelectObject(hdc,f);
    wglUseFontBitmaps(hdc,32,96,fontBase);
    SelectObject(hdc,old);
    DeleteObject(f);
#endif
}

void render_text(const char* t,int w,int h,float x,float y){
    if(!fontBase) build_font();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    glOrtho(0,w,h,0,-1,1);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glRasterPos2f(x,y);
    glListBase(fontBase-32);
    glCallLists((GLsizei)strlen(t),GL_UNSIGNED_BYTE,t);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
