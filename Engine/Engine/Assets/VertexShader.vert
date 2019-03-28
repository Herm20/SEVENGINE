#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (location = 3) uniform mat4 model;
layout (location = 4) uniform mat4 view;
layout (location = 5) uniform mat4 proj;

out vec3 posFs;
out vec2 uvFs;
out vec3 normFs;

void main(void)
{
	gl_Position = vec4(position, 1);
	uvFs = uv;
	return;

	mat4 modelView = view * model;

	gl_Position =  proj * modelView * vec4(position, 1);

	uvFs = uv;

	vec4 worldCoord4v = model * vec4(position, 1);
	posFs = vec3(
		worldCoord4v.x / worldCoord4v.w,
		worldCoord4v.y / worldCoord4v.w,
		worldCoord4v.z / worldCoord4v.w
	);

	vec4 worldNorm4v = transpose(inverse(model)) * vec4(normal, 0);
	normFs = vec3(
		worldNorm4v.x,
		worldNorm4v.y,
		worldNorm4v.z
	);
}