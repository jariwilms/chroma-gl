#version 460 core

layout (location = 0) in vec3 a_Position;

layout (binding = 0) uniform mvp
{
	mat4 model;
	mat4 view;
	mat4 projection;
};

void main()
{
    gl_Position = projection * view * model * vec4(a_Position, 1.0);
}