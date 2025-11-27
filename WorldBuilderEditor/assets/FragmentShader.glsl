###fragment
#version 410 core

layout (location = 0) out vec4 FragColor;

in vec4 iColor;
in vec2 iTexCoord;
in float iTexID;

uniform sampler2D Textures[32]; //cap

void main()
{
    FragColor = texture(Textures[int(round(iTexID))], iTexCoord) * iColor;
    // FragColor = vec4(floatBitsToUint(iTexID), floatBitsToUint(iTexID), floatBitsToUint(iTexID), 1) * iColor;
}
