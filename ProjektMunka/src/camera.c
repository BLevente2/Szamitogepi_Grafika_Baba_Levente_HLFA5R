#include "camera.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

Camera globalCamera;
vec3   globalTarget;

static float camRadius   = 10.0f;
static float camAngle    = 0.6f;
static const float minAngle   = 0.1f;
static const float maxAngle   = 1.2f;
static const float minRadius  = 5.0f;
static const float maxRadius  = 20.0f;

void adjust_camera_angle(float delta) {
    camAngle += delta;
    if (camAngle < minAngle) camAngle = minAngle;
    if (camAngle > maxAngle) camAngle = maxAngle;
}

void adjust_camera_radius(float delta) {
    camRadius += delta;
    if (camRadius < minRadius) camRadius = minRadius;
    if (camRadius > maxRadius) camRadius = maxRadius;
}

void init_camera(Camera* c) {
    float x = -cosf(camAngle) * camRadius;
    float y = sinf(camAngle) * camRadius;
    c->position = (vec3){x, y, 0.0f};
}

void update_camera(Camera* c, vec3 target) {
    float x = target.x + (-cosf(camAngle) * camRadius);
    float y = target.y + (sinf(camAngle) * camRadius);
    float z = target.z;
    c->position = (vec3){x, y, z};
    globalCamera = *c;
    globalTarget = target;
}

void apply_camera(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(globalCamera.position.x,
              globalCamera.position.y,
              globalCamera.position.z,
              globalTarget.x,
              globalTarget.y,
              globalTarget.z,
              0.0f, 1.0f, 0.0f);
}