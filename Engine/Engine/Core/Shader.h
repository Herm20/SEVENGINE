#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <boost/container/string.hpp>
#include "Types.h"
#include "Logger.h"

using namespace std;

class Shader
{
private:
	//The shader ID is the main way of referencing the shader object itself
	u32 shaderID;
	GLenum shaderType;

	bool Compile(const char* shaderSrc);
public:
	Shader(const char* shaderSrc, GLenum shaderType);
	~Shader();

	u32 GetID() const;
	GLenum GetShaderType() const;
};

#endif