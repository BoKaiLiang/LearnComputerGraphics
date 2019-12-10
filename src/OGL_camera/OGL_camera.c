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

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OGL_camera", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, on_key_callback);
    glfwSetCursorPosCallback(window, on_mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    shader_t proj_shader;
    create_shader(&proj_shader, "shaders/projection.vert", "shaders/projection.frag");

    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture 
    unsigned int texture1, texture2;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Error to load: textures/container.jpg");
        return -1;
    }
    stbi_image_free(data);
    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Error to load: textures/awesomeface.png");
        return -1;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)  
    glUseProgram(proj_shader);
    set_uniform_int(&proj_shader, "texture_box", 0);
    set_uniform_int(&proj_shader, "texture_smile", 1);

    camera_init(&camera, (vec3){ 0.0f, 0.0f, 3.0f }, GLM_YUP, YAW, PITCH);

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float current_time = glfwGetTime();
        delta_time = current_time - last_frame;
        last_frame = current_time;

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glUseProgram(proj_shader);

        // transformation, view, projection
        
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 proj = GLM_MAT4_IDENTITY_INIT;

        // glm_translate(view, (vec3){ 0.0f, 0.0f, -3.0f });
        camera_get_view_mat4(&camera, view);
        set_uniform_mat4(&proj_shader, "view", view);

        glm_perspective(glm_rad(camera.zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, proj);
        set_uniform_mat4(&proj_shader, "projection", proj);

        
        for (int i = 0; i < 10; i++) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            
            vec3 pos = GLM_VEC3_ZERO_INIT;
            for (int idx = 0; idx < 3; idx++) {
                pos[idx] = cube_positions[i][idx];
            }
            glm_translate(model, pos);
            float angle = 20.0f * (i + 1);
            glm_rotate(model, glm_rad(angle) * i, (vec3){ 1.0f, 0.3f, 0.5f });
            set_uniform_mat4(&proj_shader, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

