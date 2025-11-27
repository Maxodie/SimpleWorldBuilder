###vertex
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

struct Material
{
    float albedoTexID;
    vec4 color;
};

uniform Material uMaterial;

uniform mat4 uModelMat;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec4 iColor;
out vec2 iTexCoord;
out float iTexID;

void main()
{
    iColor = uMaterial.color;
    iTexCoord = aTexCoords;
    iTexID = uMaterial.albedoTexID;

    gl_Position =  uProjectionMatrix * uViewMatrix * uModelMat * vec4(aPos, 1.0f);
}
