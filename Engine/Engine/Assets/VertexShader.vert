#version 460 core

layout (location = 0) in vec3 position;

out vec3 color;

void main(void)
{
	color = position;
	gl_Position = vec4(position, 1);
}