#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <string>
#include <vector>

using namespace std;
class Texture
{
public:
	GLuint textID;
	string fileName;
	vector<Texture> textureManager;
	Texture();
	~Texture();

	void Use();
	void Load();
	void Unload();
};

