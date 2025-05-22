#include "app.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* ------------------------------------------------ font-helper ---- */
static GLuint fontBase = 0;
static void build_font(void){
#ifdef _WIN32
    HDC hdc = wglGetCurrentDC();
    fontBase = glGenLists(96);
    HFONT font = CreateFontA(-48,0,0,0,FW_BOLD,
                             FALSE,FALSE,FALSE,
                             ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
                             ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,
                             "Arial");
    HGDIOBJ old = SelectObject(hdc,font);
    wglUseFontBitmaps(hdc,32,96,fontBase);
    SelectObject(hdc,old);
    DeleteObject(font);
#endif
}

void render_text(const char* t,int winW,int winH,float x,float y){
    if(!fontBase) build_font();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    glOrtho(0,winW,winH,0,-1,1);
    glMatrixMode(GL_MODELVIEW);  glPushMatrix(); glLoadIdentity();

    glRasterPos2f(x,y);
    glListBase(fontBase-32);
    glCallLists((GLsizei)strlen(t),GL_UNSIGNED_BYTE,t);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/* ------------------------------------------------ OpenGL init ---- */
static void init_opengl(int w,int h){
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0,(double)w/(double)h,0.1,100.0);
}

/* ------------------------------------------------ resize ---------- */
static void reshape(GLsizei w,GLsizei h){
    glViewport(0,0,w,h);
    init_opengl(w,h);
}

/* ------------------------------------------------ init ------------ */
void init_app(App* app,int width,int height){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    app->window = SDL_CreateWindow(
        "CubestacleSDL",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        width,height,
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_MAXIMIZED
    );
    app->gl_context = SDL_GL_CreateContext(app->window);
    SDL_MaximizeWindow(app->window);
    int w,h; SDL_GetWindowSize(app->window,&w,&h);
    reshape(w,h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glFogi (GL_FOG_MODE ,GL_LINEAR);
    GLfloat fogC[4]={0.529f,0.808f,0.922f,1.0f};
    glFogfv(GL_FOG_COLOR,fogC);
    glFogf (GL_FOG_START,20.0f);
    glFogf (GL_FOG_END  ,100.0f);
    glClearColor(0.529f,0.808f,0.922f,1.0f);

    app->quit   = false;
    app->state  = STATE_MENU;
    init_camera(&app->camera);
    init_scene (&app->scene);
    init_menu  (&app->menu   ,w,h);
    init_gameover(&app->gameover,w,h);
    init_info  (&app->info   ,w,h);
    app->uptime = SDL_GetTicks()/1000.0;
}

/* ------------------------------------------------ events ---------- */
void handle_app_events(App* app,SDL_Event* e){
    if(e->type==SDL_QUIT){ app->quit=true; return; }

    if(e->type==SDL_WINDOWEVENT && e->window.event==SDL_WINDOWEVENT_RESIZED){
        reshape(e->window.data1,e->window.data2);
        init_menu   (&app->menu     ,e->window.data1,e->window.data2);
        init_gameover(&app->gameover ,e->window.data1,e->window.data2);
        init_info   (&app->info      ,e->window.data1,e->window.data2);
    }

    if(app->state==STATE_PLAYING && e->type==SDL_MOUSEWHEEL){
        adjust_camera_radius(e->wheel.y*1.0f);
    }

    if(app->state==STATE_MENU){
        menu_handle_event(&app->menu,app,e);
    }
    else if(app->state==STATE_INFO){
        info_handle_event(&app->info,app,e);
    }
    else if(app->state==STATE_GAMEOVER){
        gameover_handle_event(&app->gameover,app,e);
    }
    else if(app->state==STATE_PLAYING && e->type==SDL_KEYDOWN){
        SDL_Keycode k=e->key.keysym.sym;
        if(k==SDLK_ESCAPE)                       app->state=STATE_MENU;
        else if(k==SDLK_w||k==SDLK_UP)           adjust_camera_angle(+0.05f);
        else if(k==SDLK_s||k==SDLK_DOWN)         adjust_camera_angle(-0.05f);
        else if(k==SDLK_PLUS||k==SDLK_KP_PLUS)   adjust_camera_radius(+1.0f);
        else if(k==SDLK_MINUS||k==SDLK_KP_MINUS) adjust_camera_radius(-1.0f);
    }
}

/* ------------------------------------------------ update ---------- */
void update_app(App* app){
    double now = SDL_GetTicks()/1000.0;
    double dt  = now - app->uptime;
    app->uptime= now;

    if(app->state==STATE_MENU){
        update_menu(&app->menu,dt);
        return;
    }
    if(app->state!=STATE_PLAYING) return;

    update_camera(&app->camera,app->scene.player.box.position);
    if(update_scene(&app->scene,dt)){
        app->state = STATE_GAMEOVER;
    }
}

/* ------------------------------------------------ render ---------- */
void render_app(App* app){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    apply_camera();

    int w,h; SDL_GetWindowSize(app->window,&w,&h);

    if(app->state==STATE_PLAYING){
        render_scene(&app->scene);
        draw_score(app);
    }
    else if(app->state==STATE_MENU){
        render_menu(&app->menu,w,h);
    }
    else if(app->state==STATE_INFO){
        render_info(&app->info,w,h);
    }
    else if(app->state==STATE_GAMEOVER){
        render_gameover(&app->gameover,w,h,app->scene.player.score);
    }

    SDL_GL_SwapWindow(app->window);
}

/* ------------------------------------------------ HUD score ------- */
void draw_score(const App* app){
    int w,h; SDL_GetWindowSize(app->window,&w,&h);

    char buf[32];
    sprintf(buf,"%ld",app->scene.player.score);

    int textW = (int)strlen(buf)*24;   /* becsült szélesség */

    GLboolean depthWas = glIsEnabled(GL_DEPTH_TEST);
    if(depthWas) glDisable(GL_DEPTH_TEST);

    glColor3f(0.0f,0.0f,0.0f);
    render_text(buf,w,h,(w - textW)*0.5f,50.0f);  /* 50 px a tetejétől */

    if(depthWas) glEnable(GL_DEPTH_TEST);
}

/* ------------------------------------------------ destroy --------- */
void destroy_app(App* app){
    if(app->gl_context) SDL_GL_DeleteContext(app->gl_context);
    if(app->window)     SDL_DestroyWindow(app->window);
    IMG_Quit(); SDL_Quit();
}