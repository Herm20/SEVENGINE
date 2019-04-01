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
#include "Logger.h"

using namespace glm;
using namespace std;

class Renderer
{
private:
	//Window related variables
	GLFWwindow * window;
	i32 height = 800;
	i32 width = 1280;

	//Drawing related variables
	u32 vertexArrayID;
	u32 vertexBuffer;

	u32 indexArrayID;
	u32 indexBuffer;

	//Shader variables
	u32 mainShaderProgram;
	boost::shared_ptr<Shader> vertexShader;
	boost::shared_ptr<Shader> fragmentShader;
	const AssetManager* am;

	//Temporary proof function
	Mesh* meshes[5];
	Mesh* obj1;
	Mesh* obj2;
	Mesh* obj3;
	Mesh* obj4;

public:
	Renderer(const AssetManager* am);
	~Renderer();
	GLFWwindow* GetWindow();
	int GetWindowHeight();
	int GetWindowWidth();
	void CreateBasicProgram();
	void Draw();
	bool ShouldClose();
};

#endif
