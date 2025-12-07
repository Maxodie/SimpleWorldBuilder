###vertex
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uModelMat;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat3 uNormalMat;

out vec3 iNormal;
out vec3 iWorldPos;
out vec2 iTexCoords;

void main()
{
    iNormal = uNormalMat * aNormal;
    iTexCoords = aTexCoords;

    iWorldPos = vec3(uModelMat * vec4(aPos, 1.0f));
    gl_Position =  uProjectionMatrix * uViewMatrix * uModelMat * vec4(aPos, 1.0f);
}
