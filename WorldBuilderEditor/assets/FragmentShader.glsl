#version 330 core

out vec4 FragColor;

in vec4 iColor;
in vec2 iTexCoord;

uniform sampler2D screenTexture;


void main()
{
    FragColor = texture(screenTexture, iTexCoord) * iColor;
}
