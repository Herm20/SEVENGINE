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
	//Normal mapping
	vec3 n = normalize(fsIn.invTrans * fsIn.norm);
	vec3 t = normalize(fsIn.invTrans * fsIn.tan);
	t = normalize(t - dot(t, n) * n);
	vec3 b = normalize(fsIn.invTrans * fsIn.bitan);
	b = normalize(b - dot(b, n) * n - dot(b, t) * t);
	mat3 tbn = mat3(t, b, n);
	vec3 norm = normalize(texture(normal, fsIn.uv).xyz * 2.0 - 1.0);
	norm = normalize(tbn * norm);

	vec3 v = normalize(camPos - fsIn.pos);

	vec4 finalColor = vec4(0.0);

	norm = fsIn.invTrans * fsIn.norm;
	for(int i = 0; i < 16; i++)
	{
		vec3 l = normalize(-lights[i].dir);
		vec3 h = reflect(-l, norm);//normalize(l + v);

		vec3 tex = texture(diffuse, fsIn.uv).rgb;
		vec3 amb = 0.1 * tex;
		vec3 diff = max(dot(norm, l), 0.0) * tex;
		vec3 spec = pow(max(dot(v, h), 0.0), 256) * texture(specular, fsIn.uv).rgb;

		finalColor += vec4(lights[i].color * (amb + diff + spec), 1.0);
	}

	fragColor = finalColor;
}