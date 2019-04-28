#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
#include "AssetManager.h"
#include "Shader.h"
#include "Mesh.h"
#include "Logger.h"
#include "ECS/System.h"
#include "Systems/CameraSystem.h"
#include "Light.h"

using namespace glm;
using namespace std;

class Renderer : public ecs::System
{
private:
	//Window related variables
	GLFWwindow * window;
	i32 height = 800;
	i32 width = 1280;

	const CameraSystem* curCamera = nullptr;
	boost::container::vector<Light> lights;

public:
	explicit Renderer(ecs::Manager& manager);
	~Renderer();

	GLFWwindow* GetWindow();
	int GetWindowHeight();
	int GetWindowWidth();

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

	inline void SetCurrentCamera(const CameraSystem* cam) { this->curCamera = cam; }
	inline boost::container::vector<Light> & GetLightVector() { return this->lights; }
};

#endif
