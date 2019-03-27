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
#include "Mesh.h"


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
	Mesh* testMesh;
	glm::mat4 lookMat;
	glm::mat4 persMat;

public:
	Renderer(const AssetManager* am);
	~Renderer();
	GLFWwindow* GetWindow();
	int GetWindowHeight();
	int GetWindowWidth();
	void CreateBasicProgram();
	void Draw();
};

#endif
