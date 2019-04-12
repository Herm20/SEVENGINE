#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include "AssetManager.h"
#include "Shader.h"
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

	const AssetManager* am;
	boost::shared_ptr<Mesh> boxMesh;

public:
	Renderer();
	~Renderer();
	GLFWwindow* GetWindow();
	int GetWindowHeight();
	int GetWindowWidth();
	void CreateMeshes();
	void SetAssetManager(const AssetManager* am);
	void Draw();
};

#endif
