#ifndef MESH_RENDERER_COMPONENT_H_
#define MESH_RENDERER_COMPONENT_H_

#include "../Component.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"

struct MeshRendererComponent : public Component {
	boost::shared_ptr<Mesh> mesh;
	boost::shared_ptr<Texture> texture;
	boost::shared_ptr<ShaderProgram> shaderProgram;
};

#endif