###vertex
#version 330 core

layout (location = 0) in vec3 aPos;

struct Material
{
    int albedoTexID;
    vec2 texCoords;
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

    iColor = aColor;
    iTexCoord = aTexCoords;
    iTexID = aTexID;
}
