#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/container/string.hpp>
#include "Types.h"
#include "Shader.h"
#include "Logger.h"

class ShaderProgram
{
private:
	u32 program;

public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram &sp);
	void AttachShader(const Shader* shader);
	void Link();

	/*! \brief Uses this shader program for drawing
	 */
	inline void Use() { glUseProgram(this->program); }

	/*! \brief Gets the program id
	 */
	inline u32 GetProgram() const { return this->program; };

	const ShaderProgram & operator=(const ShaderProgram &sp);
	~ShaderProgram();
};

#endif
