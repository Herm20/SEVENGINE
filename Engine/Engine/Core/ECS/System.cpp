/**
 * @file    System.cpp
 * @ingroup ecs
 * @brief   A ecs::System manages all ecs::Entity having all required ecs::Component.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "System.h"

#include "Manager.h"

namespace ecs {

	System::System(Manager& _manager) :
		manager(_manager) {

	}

	System::~System() {

	}

	size_t System::updateEntities(float dt) {

		size_t updatedEntityCount = 0;

		for (auto entity = matchingEntities.begin(); entity != matchingEntities.end(); entity++) {
			updateEntity(dt, *entity);
			updatedEntityCount++;
		}

		return updatedEntityCount;

	}

}