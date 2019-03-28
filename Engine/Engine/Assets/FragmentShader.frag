#version 430 core

in vec3 posFs;
in vec2 uvFs;
in vec3 normFs;

void main() {

	gl_FragColor = vec4(uvFs, 0, 1);
	return;

}