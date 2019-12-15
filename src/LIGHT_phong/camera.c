#include "camera.h"
#include <math.h>

static void camera_update_vecs(camera_t* camera) {
    vec3 front = GLM_VEC3_ZERO_INIT;
    front[0] = cosf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    front[1] = sinf(glm_rad(camera->pitch));
    front[2] = sinf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    glm_vec3_normalize(front);
    camera->front[0] = front[0];
    camera->front[1] = front[1];
    camera->front[2] = front[2];

    vec3 right = GLM_VEC3_ZERO_INIT;
    glm_vec3_crossn(camera->front, camera->world_up, right);
    camera->right[0] = right[0];
    camera->right[1] = right[1];
    camera->right[2] = right[2];

    vec3 up = GLM_VEC3_ZERO_INIT;
    glm_vec3_crossn(camera->right, camera->front, up);
    camera->up[0] = up[0];
    camera->up[1] = up[1];
    camera->up[2] = up[2];
}

void camera_init(camera_t* camera, const vec3 init_pos, const vec3 init_up, const float init_yaw, const float init_pitch) {

    camera->front[0] = 0.0f;
    camera->front[1] = 0.0f;
    camera->front[2] = -1.0f;

    camera->movement_speed = SPEED;
    camera->mouse_sense = SENSITIVITY;
    camera->zoom = ZOOM;

    // Position init
    camera->pos[0] = init_pos[0];
    camera->pos[1] = init_pos[1];
    camera->pos[2] = init_pos[2];

    // Up vector init
    camera->world_up[0] = init_up[0];
    camera->world_up[1] = init_up[1];
    camera->world_up[2] = init_up[2];
    
    // Eular angles init
    camera->yaw = init_yaw;
    camera->pitch = init_pitch;

    camera_update_vecs(camera);
}

void camera_get_view_mat4(camera_t* camera, mat4 view) {
    vec3 center = GLM_VEC3_ZERO_INIT;
    glm_vec3_add(camera->pos, camera->front, center);
    glm_lookat(camera->pos, center, camera->up, view);
}

void camera_process_movement(camera_t* camera, CAM_ACTION action, const float dt) {

    float vel = camera->movement_speed * dt;
    vec3 movement = GLM_VEC3_ZERO_INIT;

    switch (action)
    {
        case FOWARD:
        {
            glm_vec3_scale(camera->front, vel, movement);
            glm_vec3_add(camera->pos, movement, camera->pos);
        }
        break;
        
        case BACKWARD:
        {
            glm_vec3_scale(camera->front, vel, movement);
            glm_vec3_sub(camera->pos, movement, camera->pos);
        }
        break;

        case LEFT:
        {
            glm_vec3_scale(camera->right, vel, movement);
            glm_vec3_sub(camera->pos, movement, camera->pos);
        }
        break;

        case RIGHT:
        {
            glm_vec3_scale(camera->right, vel, movement);
            glm_vec3_add(camera->pos, movement, camera->pos);
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