###vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

struct Material
{
    int albedoTexID;
    vec4 color;
}:

uniform Material uMaterial;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec4 iColor;
out vec2 iTexCoord;
out int iTexID;

void main()
{
    gl_Position =  uProjectionMatrix * uViewMatrix * ModelMat * vec4(aPos, 1.0f);

    iColor = uMaterial.color;
    iTexID = uMaterial.albedoTexID;
    iTexCoord = aTexCoords;
}
