#include "shader.h"

void create_shader(shader_t* shader, const char* vert_file, const char* frag_file)
{
    char* vert_src;
    char* frag_src;

    load_file_to_string(vert_file, &vert_src);
    load_file_to_string(frag_file, &frag_src);

    int sucess;
    char debug_log[1024];

    // vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const GLchar* const*)(&vert_src), NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &sucess);
    if (!sucess) {
        glGetShaderInfoLog(vertex_shader, 1024, NULL, debug_log);
        printf("ERROR: %s", &debug_log);
    }

    // fragment shader
    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const GLchar* const*)(&frag_src), NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &sucess);
    if (!sucess) {
        glGetShaderInfoLog(fragment_shader, 1024, NULL, debug_log);
        printf("ERROR: %s", &debug_log);
    }

    // link shader
    *shader = glCreateProgram();
    glAttachShader(*shader, vertex_shader);
    glAttachShader(*shader, fragment_shader);
    glLinkProgram(*shader);
    glGetProgramiv(*shader, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(*shader, 1024, NULL, debug_log);
        printf("ERROR: %s", &debug_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void set_uniform_int(shader_t* shader, const char* uni_name, int val)
{
    glUniform1i(glGetUniformLocation(*shader, uni_name), val); 
}

void set_uniform_float(shader_t* shader, const char* uni_name, float val)
{
    glUniform1f(glGetUniformLocation(*shader, uni_name), val);
}

void set_uniform_mat4(shader_t* shader, const char* uni_name, const mat4 val) {

    glUniformMatrix4fv(glGetUniformLocation(*shader, uni_name), 1, GL_FALSE, (float*)val);
}