#version 430 core

in VS_OUT
{
	vec2 uv;
	vec3 norm;
} fsIn;

uniform sampler2D tex;

out vec4 fragColor;

void main()
{
	fragColor = texture(tex, fsIn.uv);
}