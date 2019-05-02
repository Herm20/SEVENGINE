#version 430 core

layout (location = 0) in vec3 pos;

uniform mat4 cameraMatrix;

out vec texCoords;

void main(void)
{
	texCoords = pos;
	gl_Position = cameraMatrix * vec4(pos, 1.0);
}