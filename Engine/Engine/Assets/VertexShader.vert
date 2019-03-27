#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 worldLoc;
layout (location = 4) uniform mat4 cameraMatrix;

out vec3 color;

void main(void)
{
	color = position;
	gl_Position = cameraMatrix * vec4(worldLoc,1);
}