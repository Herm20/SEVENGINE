#ifndef MESH_RENDERER_COMPONENT_H_
#define MESH_RENDERER_COMPONENT_H_

#include "../ECS/Component.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"

using namespace ecs;

struct MeshRendererComponent : public Component {
	boost::shared_ptr<Mesh> mesh;
	boost::shared_ptr<Texture> texture;
	boost::shared_ptr<ShaderProgram> shaderProgram;
};

#endif