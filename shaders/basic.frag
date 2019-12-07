#version 330 core
out vec4 FragColor;

in vec2 TCoord;

uniform sampler2D texture_box;
uniform sampler2D texture_smile;

void main()
{
   FragColor = mix(texture(texture_box, TCoord), texture(texture_smile, TCoord), 0.2);
}