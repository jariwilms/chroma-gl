#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;

layout (location = 0) out vec3 color;

void main() 
{
    vec3 pos = aPos + aOffset;
    gl_Position = vec4(pos, 1.0);
    color = aOffset * 0.5 + 0.5; // Color based on offset
}