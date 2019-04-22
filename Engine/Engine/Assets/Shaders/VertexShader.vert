#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tan;
layout (location = 4) in vec3 bitan;

uniform mat4 model;
uniform mat3 invTrans;
uniform mat4 cameraMatrix;

out VS_OUT
{
	vec3 pos;
	vec2 uv;
	vec3 norm;
	vec3 tan;
	vec3 bitan;
	mat3 invTrans;
} vsOut;

void main(void)
{
	vec4 worldPos = model * vec4(position, 1.0);
	gl_Position = cameraMatrix * worldPos;

	vsOut.pos = position.xyz;
	vsOut.uv = uv;
	vsOut.norm = normal;
	vsOut.tan = tan;
	vsOut.bitan = bitan;
	vsOut.invTrans = invTrans;
}