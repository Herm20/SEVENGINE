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

#include <glm/glm.hpp>
#include <map>
#include <string>

#include "ComponentType.h"
#include "../Transform.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../ShaderProgram.h"

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
		std::map<std::string, int> map;
		void SetKey(std::string key, int value) {
			map[key] = value;
		}
	};

	struct RigidBodyComponent : public Component {
		static const ecs::ComponentType _mType = 4;
		glm::vec3 velocity = glm::vec3();
	};

	struct PlayerStateInfoComponent : public Component {
		static const ecs::ComponentType _mType = 5;
		bool isJumping = false;
		float moveSpeed = 3;
	};

	struct ColliderComponent : public Component {
		static const ecs::ComponentType _mType = 6;
		vec3 size;
		vec3 position;
		mat3 rotation;
	};

}

#endif
