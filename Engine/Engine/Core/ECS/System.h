/**
 * @file    System.h
 * @ingroup ecs
 * @brief   A ecs::System manages all ecs::Entity having all required ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "ComponentType.h"
#include "Entity.h"

#include <set>
#include <memory>

namespace ecs {

	class Manager;

	class System {

	public:

		typedef std::shared_ptr<System> Ptr;

		explicit System(Manager& _manager);
		virtual ~System();

		inline const ComponentTypeSet& getRequiredComponents() const {
			return requiredComponents;
		}

		inline bool registerEntity(Entity entity) {
			return matchingEntities.insert(entity).second;
		}

		inline size_t unregisterEntity(Entity entity) {
			return matchingEntities.erase(entity);
		}

		inline bool hasEntity(Entity entity) const {
			return (matchingEntities.end() != matchingEntities.find(entity));
		}

		size_t updateEntities(float dt);
		virtual void startFrame(float dt) = 0;
		virtual void updateEntity(float dt, Entity entity) = 0;
		virtual void endFrame(float dt) = 0;

	protected:

		inline void setRequiredComponents(ComponentTypeSet&& rc) {
			requiredComponents = std::move(rc);
		}

		Manager& manager;

	private:
		ComponentTypeSet requiredComponents;
		std::set<Entity> matchingEntities;
	};

}

#endif