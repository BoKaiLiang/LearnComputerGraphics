#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cglm/cglm.h>

typedef enum {
    FOWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CAM_ACTION;

static const float YAW         = -90.0f;
static const float PITCH       =  0.0f;
static const float SPEED       =  5.5f;
static const float SENSITIVITY =  0.1f;
static const float ZOOM        =  45.0f;

typedef struct {
    vec3 pos;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    // Euler Angles
    float yaw;
    float pitch;
    // Camera options
    float movement_speed;
    float mouse_sense;
    float zoom;
} camera_t;

void camera_init(camera_t* camera, const vec3 init_pos, const vec3 init_up, const float init_yaw, const float init_pitch);

void camera_get_view_mat4(camera_t* camera, mat4 view);

void camera_process_movement(camera_t* camera, CAM_ACTION action, const float dt);

void camera_process_fov(camera_t* camera, float x_offset, float y_offset);

void camera_process_zoom(camera_t* camera, float y_offset);

#endif // _CAMERA_H_