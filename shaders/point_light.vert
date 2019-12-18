#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{   
    FragPos = vec3(model * vec4(a_Pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * a_Normal;  
    TexCoord = a_TexCoord;
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);
}