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

	private:
		ComponentTypeSet requireComponents;
		std::set<Entity> matchingEntities;
	};

}

#endif