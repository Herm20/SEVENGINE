#include "Shader.h"

Shader::Shader(string fileName, GLenum shaderType)
{
	this->shaderType = shaderType;
	Compile(fileName);
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
	shaderID = 0;
}

//Reads the shader code from a separate file into a usable shader object
bool Shader::Compile(string fileName)
{
	//Opens the file to a binary stream
	ifstream inFile(fileName, ios::binary);
	char* fileContents;
	
	//Reads the binary stream to a char* string
	if (inFile.is_open())
	{
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();
		inFile.seekg(0, ios::beg);

		fileContents = new char[length + 1];

		inFile.read(fileContents, length);
		fileContents[length] = 0;

		inFile.close();
	}
	else
	{
		printf("A Shader Failed To Load\n");
		return false;
	}

	//Attempts to create and compile shader from char*  string
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &fileContents, 0);
	glCompileShader(shaderID);
	delete[] fileContents;

	//Determines compilation success
	GLint compilation = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilation);

	//Retrieves compilation information upon failure
	if (compilation == 0)
	{
		GLint logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* infoLog = new GLchar[logLength];
		glGetShaderInfoLog(shaderID, logLength, 0, infoLog);
		printf(infoLog);
		glDeleteShader(shaderID);
		delete[] infoLog;
		return false;
	}
	return true;
}

GLuint Shader::GetID()
{
	return shaderID;
}

GLenum Shader::GetShaderType() 
{
	return shaderType;
}
