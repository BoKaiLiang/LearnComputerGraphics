#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <cglm/cglm.h>

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "shader.h"
#include "camera.h"
#include "data.h"

// settings
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

// camera
camera_t camera;
float last_x = SCR_WIDTH / 2.0f;
float last_y = SCR_HEIGHT / 2.0f;
bool first_mouse = true;

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void on_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_process_movement(&camera, FOWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_process_movement(&camera, BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_process_movement(&camera, LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_process_movement(&camera, RIGHT, delta_time);
}

void on_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (first_mouse)
    {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top

    last_x = xpos;
    last_y = ypos;

    camera_process_fov(&camera, xoffset, yoffset);
}

void on_scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    camera_process_zoom(&camera, y_offset);
}

// directional light direction
static vec3 dir_light_dir = { -0.2f, -1.0f, -0.3f };

// point light position
static vec3 point_ligt_pos = { 1.2f, 1.0f, -6.0f };

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lighting map", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, on_key_callback);
    glfwSetCursorPosCallback(window, on_mouse_callback);
    glfwSetScrollCallback(window, on_scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    shader_t dir_light_shader, point_light_shader, lamp_shader;
    create_shader(&dir_light_shader, "shaders/dir_light.vert", "shaders/dir_light.frag");
    create_shader(&point_light_shader, "shaders/point_light.vert", "shaders/point_light.frag");
    create_shader(&lamp_shader, "shaders/lamp.vert", "shaders/lamp.frag");

    unsigned int VBO, OBJ_VAO, LIGHT_VAO;
    glGenVertexArrays(1, &OBJ_VAO);
    glGenVertexArrays(1, &LIGHT_VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind object
    glBindVertexArray(OBJ_VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Bind light
    glBindVertexArray(LIGHT_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int diffuse_texture = load_texture("textures/woodenbox.png");
    unsigned int specular_texture = load_texture("textures/steelborder.png");
    glUseProgram(dir_light_shader);
    glUseProgram(point_light_shader);
    set_uniform_int(&dir_light_shader, "material.diffuse", 0);
    set_uniform_int(&dir_light_shader, "material.specular", 1);
    set_uniform_int(&point_light_shader, "material.diffuse", 0);
    set_uniform_int(&point_light_shader, "material.specular", 1);


    // Init camera
    camera_init(&camera, (vec3){ 0.0f, 0.0f, 3.0f }, GLM_YUP, YAW, PITCH);

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float current_time = glfwGetTime();
        delta_time = current_time - last_frame;
        last_frame = current_time;

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OBJECT //
#if 0
        //// PROCESS DIRECTIONAL LIGHT ////
        glUseProgram(dir_light_shader);

        set_uniform_vec3(&dir_light_shader, "light.direction", dir_light_dir);
        set_uniform_vec3(&dir_light_shader, "viewPos", camera.pos);

        // transformation, view, projection
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 proj = GLM_MAT4_IDENTITY_INIT;

        // directional light properties
        vec3 light_color = GLM_VEC3_ONE_INIT;

        vec3 diffuse_color = GLM_VEC3_ZERO_INIT;
        glm_vec3_scale(light_color, 0.5f, diffuse_color);

        vec3 ambient_color = GLM_VEC3_ZERO_INIT;
        glm_vec3_scale(diffuse_color, 0.2f, ambient_color);

        set_uniform_vec3(&dir_light_shader, "light.ambient", ambient_color);
        set_uniform_vec3(&dir_light_shader, "light.diffuse", diffuse_color);
        set_uniform_vec3(&dir_light_shader, "light.specular", GLM_VEC3_ONE);

        // material properties
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture);
        set_uniform_float(&dir_light_shader, "material.shininess", 32.0f);

        // transformation
        camera_get_view_mat4(&camera, view);
        set_uniform_mat4(&dir_light_shader, "view", view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, proj);
        set_uniform_mat4(&dir_light_shader, "projection", proj);

        glBindVertexArray(OBJ_VAO);
        for (int i = 0; i < 10; i++) {
            
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            vec3 pos = GLM_VEC3_ZERO_INIT;
            for (int idx = 0; idx < 3; idx++) {
                pos[idx] = cubePositions[i][idx];
            }
            glm_translate(model, pos);
            float angle = 20.0f * i;
            glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            set_uniform_mat4(&dir_light_shader, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
#endif
        
        //// PROCESS POINT LIGHT ////
        glUseProgram(point_light_shader);

        set_uniform_vec3(&point_light_shader, "light.position", point_ligt_pos);
        set_uniform_vec3(&point_light_shader, "viewPos", camera.pos);

        // transformation, view, projection
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 proj = GLM_MAT4_IDENTITY_INIT;

        // directional light properties
        vec3 light_color = GLM_VEC3_ONE_INIT;

        vec3 diffuse_color = GLM_VEC3_ZERO_INIT;
        glm_vec3_scale(light_color, 0.5f, diffuse_color);

        vec3 ambient_color = GLM_VEC3_ZERO_INIT;
        glm_vec3_scale(diffuse_color, 0.2f, ambient_color);

        set_uniform_vec3(&point_light_shader, "light.ambient", ambient_color);
        set_uniform_vec3(&point_light_shader, "light.diffuse", diffuse_color);
        set_uniform_vec3(&point_light_shader, "light.specular", GLM_VEC3_ONE);
        set_uniform_float(&point_light_shader, "light.constant", 1.0f);
        set_uniform_float(&point_light_shader, "light.linear", 0.09f);
        set_uniform_float(&point_light_shader, "light.constant", 0.032f);

        // material properties
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture);
        set_uniform_float(&point_light_shader, "material.shininess", 32.0f);

        // transformation
        camera_get_view_mat4(&camera, view);
        set_uniform_mat4(&point_light_shader, "view", view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, proj);
        set_uniform_mat4(&point_light_shader, "projection", proj);

        glBindVertexArray(OBJ_VAO);
        for (int i = 0; i < 10; i++) {
            
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            vec3 pos = GLM_VEC3_ZERO_INIT;
            for (int idx = 0; idx < 3; idx++) {
                pos[idx] = cubePositions[i][idx];
            }
            glm_translate(model, pos);
            float angle = 20.0f * i;
            glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            set_uniform_mat4(&point_light_shader, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // RENDER LAMP //
        glUseProgram(lamp_shader);

        // transformation, view, projection
        mat4 l_view = GLM_MAT4_IDENTITY_INIT;
        mat4 l_proj = GLM_MAT4_IDENTITY_INIT;
        mat4 l_model = GLM_MAT4_IDENTITY_INIT;

        camera_get_view_mat4(&camera, l_view);
        set_uniform_mat4(&lamp_shader, "view", l_view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, l_proj);
        set_uniform_mat4(&lamp_shader, "projection", l_proj);

        
        glm_translate(l_model, point_ligt_pos);
        glm_scale_uni(l_model, 0.2f);
        set_uniform_mat4(&lamp_shader, "model", l_model);
        
        set_uniform_vec3(&lamp_shader, "LightColor", light_color);

        glBindVertexArray(LIGHT_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &LIGHT_VAO);
    glDeleteVertexArrays(1, &OBJ_VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}



