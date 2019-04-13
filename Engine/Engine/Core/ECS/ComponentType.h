/**
 * @file    ComponentType.h
 * @ingroup ecs
 * @brief   A ecs::ComponentType is a positive Id referencing a type of ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef ECS_COMPONENT_TYPE
#define ECS_COMPONENT_TYPE

#include <set>

namespace ecs {
	typedef unsigned int ComponentType;
	static const ComponentType _invalidComponentType = 0;
	typedef std::set<ComponentType> ComponentTypeSet;
}

#endif