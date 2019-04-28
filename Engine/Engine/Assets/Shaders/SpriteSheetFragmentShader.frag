#version 430 core

in VS_OUT
{
	vec2 uv;
} fsIn;

uniform sampler2D diffuse;

out vec4 fragColor;

void main()
{
	fragColor = texture(diffuse, fsIn.uv);
}