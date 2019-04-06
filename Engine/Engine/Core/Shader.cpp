#include "Shader.h"

Shader::Shader(const char* shaderSrc, GLenum shaderType)
{
	this->shaderType = shaderType;
	Compile(shaderSrc);
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
	shaderID = 0;
}

//Reads the shader code from a separate file into a usable shader object
bool Shader::Compile(const char* shaderSrc)
{
	//Attempts to create and compile shader from char* string
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSrc, 0);
	glCompileShader(shaderID);

	//Determines compilation success
	i32 compilation = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilation);

	//Retrieves compilation information upon failure
	if (compilation == 0)
	{
		i32 logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* infoLog = new GLchar[logLength];
		glGetShaderInfoLog(shaderID, logLength, 0, infoLog);
		Logger::Log(Logger::LogType::ERROR, infoLog);
		glDeleteShader(shaderID);
		delete[] infoLog;
		return false;
	}
	return true;
}

u32 Shader::GetID() const
{
	return shaderID;
}

GLenum Shader::GetShaderType() const
{
	return shaderType;
}