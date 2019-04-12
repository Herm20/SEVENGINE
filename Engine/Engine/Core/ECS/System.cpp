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