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

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Color", NULL, NULL);
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
    shader_t obj_shader, lamp_shader;
    create_shader(&obj_shader, "shaders/color.vert", "shaders/color.frag");
    create_shader(&lamp_shader, "shaders/color.vert", "shaders/lamp.frag");

    
    unsigned int VBO, OBJ_VAO, LIGHT_VAO;
    glGenVertexArrays(1, &OBJ_VAO);
    glGenVertexArrays(1, &LIGHT_VAO);
    glGenBuffers(1, &VBO);

    // Bind object
    glBindVertexArray(OBJ_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind light
    glBindVertexArray(LIGHT_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Init camera
    camera_init(&camera, (vec3){ 0.0f, 0.0f, 3.0f }, GLM_YUP, YAW, PITCH);

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float current_time = glfwGetTime();
        delta_time = current_time - last_frame;
        last_frame = current_time;

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Light color
        vec3 light_color = { 1.0f, 1.0f, 1.0f };

        // OBJECT //
        glUseProgram(obj_shader);

        // transformation, view, projection
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 proj = GLM_MAT4_IDENTITY_INIT;
        mat4 model = GLM_MAT4_IDENTITY_INIT;

        camera_get_view_mat4(&camera, view);
        set_uniform_mat4(&obj_shader, "view", view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, proj);
        set_uniform_mat4(&obj_shader, "projection", proj);

        glm_translate(model, GLM_VEC3_ZERO);
        set_uniform_mat4(&obj_shader, "model", model);
        
        set_uniform_vec3(&obj_shader, "ObjColor", (vec3){1.0f, 0.5f, 0.31f});
        set_uniform_vec3(&obj_shader, "LightColor", light_color);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // LIGHT //
        glUseProgram(lamp_shader);

        // transformation, view, projection
        mat4 l_view = GLM_MAT4_IDENTITY_INIT;
        mat4 l_proj = GLM_MAT4_IDENTITY_INIT;
        mat4 l_model = GLM_MAT4_IDENTITY_INIT;

        camera_get_view_mat4(&camera, l_view);
        set_uniform_mat4(&lamp_shader, "view", l_view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, l_proj);
        set_uniform_mat4(&lamp_shader, "projection", l_proj);

        glm_translate(l_model, (vec3){1.2f, 1.0f, 2.0f});
        glm_scale(l_model, (vec3){0.2f, 0.2f, 0.2f});
        set_uniform_mat4(&lamp_shader, "model", l_model);
        
        set_uniform_vec3(&obj_shader, "LightColor", light_color);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &OBJ_VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

