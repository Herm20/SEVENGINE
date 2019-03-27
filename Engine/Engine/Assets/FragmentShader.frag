#version 460 core
layout (location = 5) uniform vec3 camLocation;

in vec3 color;

void main(void)
{
	gl_FragColor = vec4(color, 1);
}