#ifndef ECS_COMPONENT_TYPE
#define ECS_COMPONENT_TYPE

#include <set>

namespace ecs {
	typedef unsigned int ComponentType;
	static const ComponentType _invalidComponentType = 0;
	typedef std::set<ComponentType> ComponentTypeSet;
}

#endif