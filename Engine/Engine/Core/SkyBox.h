#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "Mesh.h"
#include "AssetManager.h"
#include "ShaderProgram.h"
#include "Systems/Camera.h"

class SkyBox
{
private:
	boost::shared_ptr<Mesh> skyMesh;
	boost::shared_ptr<ShaderProgram> skyShaders;
public:
	SkyBox();
	SkyBox(AssetManager * assets);
	void Render(CameraSystem * cam);
	~SkyBox();
};
#endif