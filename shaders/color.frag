#version 330 core

out vec4 FragColor;

uniform vec3 ObjColor;
uniform vec3 LightColor;

void main() {
    FragColor = vec4(LightColor * ObjColor, 1.0);
}