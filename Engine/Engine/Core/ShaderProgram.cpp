#include "ShaderProgram.h"

/*! \brief Shader program constructor. Generates the program id
 */
ShaderProgram::ShaderProgram()
{
	this->program = glCreateProgram();
}

/*! \brief Shader program copy constructor
 * \param (const ShaderProgram &) sp - The shader program to copy
 */
ShaderProgram::ShaderProgram(const ShaderProgram &sp)
{
	this->program = sp.program;
}

/*! \brief Attaches a shader to the program
 *
 * \param (const Shader*) shader - Pointer to the shader to attach
 */
void ShaderProgram::AttachShader(const Shader* shader)
{
	glAttachShader(this->program, shader->GetID());
}

/*! \brief Links the shader program
 */
void ShaderProgram::Link()
{
	int32_t success;
	char infoLog[512];

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if(!success) {
		glGetProgramInfoLog((this->program), 512, nullptr, infoLog);
		Logger::Log(Logger::ERROR, infoLog);
	}

	//Detach shaders from program
	uint32_t shaders[6] = {};
	int32_t count = 0;

	glGetAttachedShaders(this->program, 6, &count, shaders);

	for(int i = 0; i < count; i++) {
		glDetachShader(this->program, shaders[i]);
	}
}

/*! \brief Copy assignment operator
 *
 * \param (const ShaderProgram &) sp - The shader program to copy
 *
 * \return (const ShaderProgram &) This shader program after copying
 */
const ShaderProgram & ShaderProgram::operator=(const ShaderProgram &sp)
{
	this->program = sp.program;
	return *this;
}

/*! \brief Destructor for a shader program. Just general cleanup
 */
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->program);
}
