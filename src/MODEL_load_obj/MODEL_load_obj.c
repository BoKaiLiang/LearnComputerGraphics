/* credit from: https://github.com/zauonlok/renderer/ */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include "../MATH/camera.h"
#include "../MATH/shader.h"
#include "../MATH/data.h"
#include "../MATH/utilm.h"
#include "../MATH/mat.h"

#include "util.h"
#include "dyarray.h"
#include "mesh.h"


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Load obj", NULL, NULL);
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // build and compile our shader program
    shader_t model_shader;
    create_shader(&model_shader, "shaders/model.vert", "shaders/model.frag");

    // MODEL

    mesh_t* mesh = NULL;
    mesh = mesh_load("models/objs/witch.obj");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3_t) * mesh->num_positions, &mesh->positions[0], GL_STATIC_DRAW);
    

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3_t), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    camera_init(&camera, (vec3_t){ 0.0f, 0.0f, 3.0f }, (vec3_t){ 0.0f, 1.0f, 0.0f }, YAW, PITCH);

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float current_time = glfwGetTime();
        delta_time = current_time - last_frame;
        last_frame = current_time;

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(model_shader);
        mat4_t view = mat4_identity();
        mat4_t proj = mat4_identity();
        view = camera_get_view_mat4(&camera);
        proj = mat4_perspective(utilm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        set_uniform_mat4(&model_shader, "view", view);
        set_uniform_mat4(&model_shader, "projection", proj);

        mat4_t m = mat4_identity();
        m = mat4_translate(m, -3.0f, 0.0f, -3.0f);
        m = mat4_scale(m, 0.2f, 0.2f, 0.2f);
        set_uniform_mat4(&model_shader,"model", m);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh->num_positions);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}