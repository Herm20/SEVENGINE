#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tan;
layout (location = 4) in vec3 bitan;

uniform mat4 model;
uniform mat4 cameraMatrix;

out VS_OUT
{
	vec2 uv;
} vsOut;

void main(void)
{
	gl_Position = cameraMatrix * model * vec4(position, 1.0);
	vsOut.uv = uv;
}