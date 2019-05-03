/**
 * @file    Manager.cpp
 * @ingroup ecs
 * @brief   Manage associations of ecs::Entity, ecs::Component and ecs::System.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Manager.h"

#include <algorithm>
#include <iostream>
namespace ecs{

	Manager::Manager() :
		mLastEntity(_invalidEntity),
		entities(),
		componentStores(),
		systems() {

	}

	Manager::~Manager() {

	}

	void Manager::addSystem(const System::Ptr& _systemPtr) {
		if ((!_systemPtr) || (_systemPtr->getRequiredComponents().empty())) {
			throw std::runtime_error("System shall specify required Components");
		}
		systems.push_back(_systemPtr);
	}

	size_t Manager::registerEntity(const Entity _entity) {

		size_t associatedSystemsCount = 0;

		auto entity = entities.find(_entity);
		if (entities.end() == entity) {
			throw std::runtime_error("The Entity does not exist");
		}
		auto entityComponents = (*entity).second;

		for (auto system = systems.begin(); system != systems.end(); system++) {
			auto systemRequiredComponents = (*system)->getRequiredComponents();
			if (std::includes(
				entityComponents.begin(), entityComponents.end(),
				systemRequiredComponents.begin(), systemRequiredComponents.end())) {
				(*system)->registerEntity(_entity);
				associatedSystemsCount++;
			}
		}

		return associatedSystemsCount;

	}

	size_t Manager::unregisterEntity(const Entity _entity) {

		size_t associatedSystemsCount = 0;

		auto entity = entities.find(_entity);
		if (entities.end() == entity) {
			throw std::runtime_error("The Entity does not exist");
		}
		auto entityComponents = (*entity).second;

		getComponentStore<ecs::ColliderComponent>().remove(_entity);
		getComponentStore<ecs::TransformComponent>().remove(_entity);
		getComponentStore<ecs::MeshRendererComponent>().remove(_entity);

		for (auto system = systems.begin(); system != systems.end(); system++) {
			associatedSystemsCount += (*system)->unregisterEntity(_entity);
		}

		return associatedSystemsCount;

	}

	size_t Manager::updateEntities(float _dt) {

		size_t updatedEntitiesCount = 0;

		// Start Frame
		for (auto system = systems.begin(); system != systems.end(); system++) {
			(*system)->startFrame(_dt);
		}

		// Update Entities
		for (auto system = systems.begin(); system != systems.end(); system++) {
			updatedEntitiesCount += (*system)->updateEntities(_dt);
		}

		// End Frame
		for (auto system = systems.begin(); system != systems.end(); system++) {
			(*system)->endFrame(_dt);
		}

		return updatedEntitiesCount;

	}

}