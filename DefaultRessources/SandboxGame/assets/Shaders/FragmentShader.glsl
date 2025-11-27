###fragment
#version 330 core

out vec4 FragColor;

in vec4 iColor;
in vec2 iTexCoord;
in int iTexID;

uniform sampler2D Textures[32]; //cap

void main()
{
    FragColor =  iColor;
}
