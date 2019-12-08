#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_box;
uniform sampler2D texture_smile;

void main()
{
   FragColor = mix(texture(texture_box, TexCoord), texture(texture_smile, TexCoord), 0.2);
}