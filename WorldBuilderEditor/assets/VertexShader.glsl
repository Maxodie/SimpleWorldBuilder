#version 330 core

layout (location = 0) in vec4 aColor;
layout (location = 1) in vec3 aPos;
layout (location = 2) in vec3 aScale;

out vec4 oColor;

void main()
{
    vec3 pos = aPos * aScale;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

    oColor = aColor;
}
