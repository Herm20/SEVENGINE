#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ComponentType.h"

#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"

namespace ecs {

	struct Component {
		static const ComponentType _mtype = 1;
	};

	struct MeshRendererComponent : public Component {
		boost::shared_ptr<Mesh> mesh;
		boost::shared_ptr<Texture> texture;
		boost::shared_ptr<ShaderProgram> shaderProgram;
	};
	//const ecs::ComponentType MeshRendererComponent::_mtype = 1;

}

#endif
