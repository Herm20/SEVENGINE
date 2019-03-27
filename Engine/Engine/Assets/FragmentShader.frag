#version 460 core

uniform sampler2D tex;

layout (location = 6) uniform vec3 lightPos;
layout (location = 7) uniform vec3 camPos;

in vec3 posFs;
in vec2 uvFs;
in vec3 normFs;

void main() {

	gl_FragColor = vec4(uvFs, 0, 1);
	return;

	vec3 L = normalize(lightPos - posFs);
	vec3 V = normalize(camPos - posFs);
	vec3 H = normalize(L + V);
	vec3 N = normalize(normFs);

	float cA = 0.4f;
	float cD = 0.8f;
	float cS = 0.4f;

	vec3 ambient = vec3(cA);
	vec3 diffuse = vec3(cD) * max( dot(L,N), 0 );
	vec3 specular = vec3(cS) * pow( max( dot(H,N), 0 ), 16.f );
	vec3 brightness = ambient + diffuse + specular;

	vec4 texColor = texture(tex, uvFs);
	gl_FragColor = texColor * vec4(brightness, 1);

}