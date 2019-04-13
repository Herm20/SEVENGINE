#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

#include "Entity.h"
#include "Component.h"
#include "ComponentType.h"
/**
 * @file    Manager.h
 * @ingroup ecs
 * @brief   Manage associations of ecs::Entity, ecs::Component and ecs::System.
 *
 * Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "ComponentStore.h"
#include "System.h"

#include <map>
#include <vector>
#include <cassert>

namespace ecs {

	class Manager {

	public:

		Manager();
		virtual ~Manager();

		template<typename C>
		inline bool createComponentStore() {
			static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
			static_assert(C::_mType != _invalidComponentType, "C must define a valid non-zero type");
			return componentStores.insert(std::make_pair(C::_mType, IComponentStore::Ptr(new ComponentStore<C>()))).second;
		}

		template<typename C>
		inline ComponentStore<C>& getComponentStore() {
			static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
			static_assert(C::_mType != _invalidComponentType, "C must define a valid non-zero _mType");
			auto iComponentStore = componentStores.find(C::_mType);
			if (componentStores.end() == iComponentStore) {
				throw std::runtime_error("The ComponentStore does not exist");
			}
			return reinterpret_cast<ComponentStore<C>&>(*(iComponentStore->second));
		}

		void addSystem(const System::Ptr& _systemPtr);

		inline Entity createEntity() {
			assert(mLastEntity < std::numeric_limits<Entity>::max());
			entities.insert(std::make_pair((mLastEntity + 1), ComponentTypeSet()));
			return (++mLastEntity);
		}

		template<typename C>
		inline bool addComponent(const Entity _entity, C&& _component) {
			static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
			static_assert(C::_mType != _invalidComponentType, "C must define a valid non-zero type");
			auto entity = entities.find(_entity);
			if (entities.end() == entity) {
				throw std::runtime_error("The Entity does not exist");
			}
			(*entity).second.insert(C::_mType);
			return getComponentStore<C>().add(_entity, std::move(_component));
		}

		size_t registerEntity(const Entity _entity);
		size_t unregisterEntity(const Entity _entity);
		size_t updateEntities(float _dt);

	private:

		Entity mLastEntity;
		std::unordered_map<Entity, ComponentTypeSet> entities;
		std::map<ComponentType, IComponentStore::Ptr> componentStores;
		std::vector<System::Ptr> systems;

	};

}

#endif