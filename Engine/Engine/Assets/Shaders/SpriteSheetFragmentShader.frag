#version 430 core

in VS_OUT
{
	vec2 uv;
} fsIn;

uniform sampler2D diffuse;

uniform vec2 scaleSize;
uniform vec2 offset;

out vec4 fragColor;

void main()
{
	vec2 uv = (fsIn.uv * scaleSize) + offset;

	vec4 color = texture(diffuse, uv);

	if(color.a < 0.25)
		discard;

	fragColor = color;
}