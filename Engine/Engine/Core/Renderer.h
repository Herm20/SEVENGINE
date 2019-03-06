#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class Renderer
{
private:
	//Window related variables
	GLFWwindow * window;
	int height = 480;
	int width = 640;

	//Drawing related variables
	GLuint vertexArrayID;
	GLuint vertexBuffer;

	//Temporary proof function
	void CreateTriangle();
public:
	Renderer();
	~Renderer();
	GLFWwindow* GetWindow();
	void Draw();
};

#endif
