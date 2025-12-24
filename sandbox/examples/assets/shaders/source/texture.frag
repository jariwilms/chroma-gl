#version 460 core

layout (location = 0) in  vec2 v_TexCoord;
layout (location = 0) out vec4 f_Color;

layout (binding  = 0) uniform sampler2D texture1;

void main()
{
    f_Color = texture(texture1, v_TexCoord);
}