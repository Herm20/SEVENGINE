#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include "Shader.h"

using namespace glm;
using namespace std;

class Renderer
{
private:
	//Window related variables
	GLFWwindow * window;
	int height = 800;
	int width = 1280;

	//Drawing related variables
	GLuint vertexArrayID;
	GLuint vertexBuffer;

	//Shader variables
	GLuint mainShaderProgram;
	Shader* vertexShader;
	Shader* fragmentShader;

	//Temporary proof function
	void CreateTriangle();
public:
	Renderer();
	~Renderer();
	GLFWwindow* GetWindow();
	bool LoadShaders();
	void Draw();
};

#endif
