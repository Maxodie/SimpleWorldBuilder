#version 330 core

layout (location = 0) in vec4 aColor;
layout (location = 1) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 uModelMat;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec4 iColor;
out vec2 iTexCoord;

void main()
{
    gl_Position =  uProjectionMatrix * uViewMatrix * uModelMat * vec4(aPos, 1.0f);

    iColor = aColor;
    iTexCoord = aTexCoords;

}
