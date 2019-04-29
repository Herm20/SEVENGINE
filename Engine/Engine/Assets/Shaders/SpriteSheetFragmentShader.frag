#version 430 core

in VS_OUT
{
	vec2 uv;
} fsIn;

uniform sampler2D diffuse;

uniform vec2 scaleSize;

out vec4 fragColor;

void main()
{
	vec2 uv = (fsIn.uv * vec2(0.05, 0.08)) + vec2(0, 0.92);
	vec4 color = texture(diffuse, uv);

	if(color.a < 0.25)
		discard;

	fragColor = color;
}