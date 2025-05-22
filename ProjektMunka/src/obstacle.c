#include "obstacle.h"
#include <math.h>
#include <stdlib.h>

static float randf(float a,float b){
    return a + ((float)rand() / (float)RAND_MAX)*(b-a);
}

/* ciklikus színlista 150 score-onkét */
static Color color_from_score(long score){
    const Color colors[]={
        {0.0f,0.0f,1.0f},   /* kék   */
        {0.5f,0.0f,0.5f},   /* lila  */
        {1.0f,0.0f,0.0f},   /* piros */
        {1.0f,0.4f,0.7f},   /* pink  */
        {0.0f,1.0f,0.0f}    /* zöld  */
    };
    int idx = (score/150)% (sizeof(colors)/sizeof(colors[0]));
    return colors[idx];
}

void init_obstacle(Obstacle* o,vec3 pos,vec3 size,long score){
    Color c = color_from_score(score);
    init_rectangular_prism(&o->box,size.x,size.y,size.z,c,pos);
    set_rectangular_prism_rotation(&o->box,randf(-15.0f,15.0f));
}

void draw_obstacle(const Obstacle* o){
    draw_rectangular_prism(&o->box);
}

bool check_obstacle_collision(const Obstacle* o,const Player* p){
    vec3 aPos=p->box.position, aSize=p->box.size;
    vec3 bPos=o->box.position, bSize=o->box.size;
    return (fabsf(aPos.x-bPos.x)*2.0f<(aSize.x+bSize.x)) &&
           (fabsf(aPos.y-bPos.y)*2.0f<(aSize.y+bSize.y)) &&
           (fabsf(aPos.z-bPos.z)*2.0f<(aSize.z+bSize.z));
}