#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (location = 3) uniform mat4 model;
layout (location = 4) uniform mat4 view;
layout (location = 5) uniform mat4 proj;

layout (location = 8) uniform mat4 cameraMatrix;

out vec3 posFs;
out vec2 uvFs;
out vec3 normFs;

void main(void)
{
	gl_Position = cameraMatrix * vec4(position,1);

	uvFs = uv;
	return;

}