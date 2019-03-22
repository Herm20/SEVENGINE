#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>

using namespace std;

class Shader
{
private:
	//The shader ID is the main way of referencing the shader object itself
	GLuint shaderID;
	GLenum shaderType;
	
	bool Compile(string fileName);
public:
	Shader(string fileName, GLenum shaderType);
	~Shader();
	
	GLuint GetID();
	GLenum GetShaderType();
};

#endif