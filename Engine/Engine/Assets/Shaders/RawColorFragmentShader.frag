#version 430 core

struct Light
{
	vec3 pos;
	float radius;
	vec3 color;
	float intensity;
	vec3 dir;
};

in VS_OUT
{
	vec3 pos;
	vec2 uv;
	vec3 norm;
	vec3 tan;
	vec3 bitan;
	mat3 invTrans;
} fsIn;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D specular;

uniform vec3 camPos;
uniform Light lights[16];

out vec4 fragColor;

//TODO: Fix the lighting in here

void main()
{
	vec3 tex = texture(diffuse, fsIn.uv).rgb;
	fragColor = vec4(tex, 1);
}