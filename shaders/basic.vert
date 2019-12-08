#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(a_Pos, 1.0);
    TexCoord = a_TexCoord;
}