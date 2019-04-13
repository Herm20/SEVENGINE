#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ComponentType.h"

#include <glm/glm.hpp>

#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"

namespace ecs {

	struct Component {
		static const ComponentType _mType = _invalidComponentType;
	};

	struct TransformComponent : public Component {
		static const ecs::ComponentType _mType = 1;
		glm::vec3 position;
	};

	struct MeshRendererComponent : public Component {
		static const ecs::ComponentType _mType = 2;
		boost::shared_ptr<Mesh> mesh;
		boost::shared_ptr<Texture> texture;
		boost::shared_ptr<ShaderProgram> shaderProgram;
	};

}

#endif
