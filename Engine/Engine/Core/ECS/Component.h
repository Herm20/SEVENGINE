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
#include <boost/container/string.hpp>
#include <map>
#include <string>

#include "ComponentType.h"
#include <glm/glm.hpp>
#include "../Transform.h"
#include "../Mesh.h"
#include "../Material.h"
#include "../Light.h"
#include "../Types.h"

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
		boost::shared_ptr<Material> material;
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

	struct LightComponent : public Component {
		static const ecs::ComponentType _mType = 6;
		Light light;
	};

	struct ScriptComponent : public Component {
		static const ecs::ComponentType _mType = 7;
		boost::container::string path;
		u64 id = U64_MAX;
	};

	struct CameraComponent : public Component {
		static const ecs::ComponentType _mType = 8;

	};
}

#endif
