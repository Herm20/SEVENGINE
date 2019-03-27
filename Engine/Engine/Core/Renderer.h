#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include "AssetManager.h"
#include "Shader.h"
#include "Entity.h"

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
	boost::shared_ptr<Shader> vertexShader;
	boost::shared_ptr<Shader> fragmentShader;
	const AssetManager* am;
	Entity* dummyEnt;

	//Temporary proof function
	void CreateTriangle();
public:
	Renderer(const AssetManager* am);
	~Renderer();
	GLFWwindow* GetWindow();
	void CreateBasicProgram();
	void Draw();
	void DrawEntity(Entity* _entity);
};

#endif
