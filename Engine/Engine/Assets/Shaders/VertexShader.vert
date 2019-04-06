#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (location = 3) uniform mat4 model;
layout (location = 4) uniform mat4 view;
layout (location = 5) uniform mat4 proj;

layout (location = 8) uniform mat4 cameraMatrix;

out VS_OUT
{
	vec2 uv;
	vec3 norm;
} vsOut;

void main(void)
{
	vec4 worldPos = model * vec4(position, 1.0);
	gl_Position = cameraMatrix * worldPos;

	vsOut.uv = uv;
	vsOut.norm = normal;
}