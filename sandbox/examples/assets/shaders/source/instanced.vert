#version 460 core

layout (location = 0) in  vec3 a_Position;
layout (location = 1) in  vec3 a_Offset;

layout (location = 0) out vec3 v_Color;

void main() 
{
    vec3 position = a_Position + a_Offset;
    gl_Position   = vec4(position, 1.0);
    v_Color       = a_Offset * 0.5 + 0.5; // Color based on offset
}