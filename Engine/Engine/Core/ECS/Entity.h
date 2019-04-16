/**
 * @file    Entity.h
 * @ingroup ecs
 * @brief   An ecs::Entity is an Id referencing a game object.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

namespace ecs {
	typedef unsigned int Entity;
	static const Entity _invalidEntity = 0;
}

#endif
