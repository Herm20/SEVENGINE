/**
 * @file    Component.h
 * @ingroup ecs
 * @brief   A ecs::Component keep the data for one aspect of an ecs::Entity.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ComponentType.h"

#include <glm/glm.hpp>
#include "../Transform.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"
#include <vector>

namespace ecs {

	struct Component {
		static const ComponentType _mType = _invalidComponentType;
	};

	struct TransformComponent : public Component {
		static const ecs::ComponentType _mType = 1;
		Transform transform;
	};

	struct MeshRendererComponent : public Component {
		static const ecs::ComponentType _mType = 2;
		boost::shared_ptr<Mesh> mesh;
		boost::shared_ptr<Texture> texture;
		boost::shared_ptr<ShaderProgram> shaderProgram;
	};

	struct KeyboardInputComponent : public Component {
		static const ecs::ComponentType _mType = 3;
		// keyboard mapping
			
	};

	struct RigidBodyComponent : public Component {
		static const ecs::ComponentType _mType = 4;
		glm::vec3 velocity = glm::vec3();
	};

	struct PlayerStateInfoComponent : public Component {
		static const ecs::ComponentType _mType = 5;
		bool isJumping = false;
		float wiggleRate = 0.0f;
		float jumpRate = 5.0f;
		float jumpTimer = 0.0f;
	};

}

#endif
