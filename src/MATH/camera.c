#include "camera.h"
#include <math.h>

static void camera_update_vecs(camera_t* camera) {

    camera->front = vec3_norm(vec3_init(
        cosf(utilm_rad(camera->yaw)) * cosf(utilm_rad(camera->pitch)),
        sinf(utilm_rad(camera->pitch)),
        sinf(utilm_rad(camera->yaw)) * cosf(utilm_rad(camera->pitch))
    ));

    camera->right = vec3_norm(vec3_cross(camera->front, camera->world_up));

    camera->up = vec3_norm(vec3_cross(camera->right, camera->front));
}

void camera_init(camera_t* camera, const vec3_t init_pos, const vec3_t init_up, const float init_yaw, const float init_pitch) {

    camera->front = vec3_init(0.0f, 0.0f, -1.0f);

    camera->movement_speed = SPEED;
    camera->mouse_sense = SENSITIVITY;
    camera->zoom = ZOOM;

    // Position init
    camera->pos = init_pos;

    // Up vector init
    camera->world_up = init_up;
    
    // Eular angles init
    camera->yaw = init_yaw;
    camera->pitch = init_pitch;

    camera_update_vecs(camera);
}

mat4_t camera_get_view_mat4(camera_t* camera) {
    vec3_t center = vec3_add(camera->pos, camera->front);
    return mat4_lookat(camera->pos, center, camera->up);
}

void camera_process_movement(camera_t* camera, CAM_ACTION action, const float dt) {

    float vel = camera->movement_speed * dt;

    switch (action)
    {
        case FOWARD:
        {
            camera->pos = vec3_add(camera->pos, vec3_scale(camera->front, vel));
        }
        break;
        
        case BACKWARD:
        {
            camera->pos = vec3_sub(camera->pos, vec3_scale(camera->front, vel));
        }
        break;

        case LEFT:
        {
            camera->pos = vec3_sub(camera->pos, vec3_scale(camera->right, vel));
        }
        break;

        case RIGHT:
        {
            camera->pos = vec3_add(camera->pos, vec3_scale(camera->right, vel));
        }
        break;

    default:
        break;
    }
}

void camera_process_fov(camera_t* camera, float x_offset, float y_offset) {
    x_offset *= camera->mouse_sense;
    y_offset *= camera->mouse_sense;

    camera->yaw += x_offset;
    camera->pitch += y_offset;

    camera->pitch = (camera->pitch > 89.9f) ? 89.9f : camera->pitch;
    camera->pitch = (camera->pitch < -89.9f) ? -89.9f : camera->pitch;

    camera_update_vecs(camera);
}

void camera_process_zoom(camera_t* camera, float y_offset) {
    
    if (camera->zoom >= 1.0f && camera->zoom <= 45.0f)
            camera->zoom -= y_offset;
    if (camera->zoom <= 1.0f)
        camera->zoom = 1.0f;
    if (camera->zoom >= 45.0f)
        camera->zoom = 45.0f;
}