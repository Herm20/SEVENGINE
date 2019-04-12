#ifndef ECS_COMPONENT_STORE_H
#define ECS_COMPONENT_STORE_H

#include "Entity.h"
#include "Component.h"

#include <unordered_map>
#include <memory>

namespace ecs {

	class IComponentStore {
	public:
		typedef std::unique_ptr<IComponentStore> Ptr;
	};

	template<typename C>
	class ComponentStore : public IComponentStore {

	public:

		ComponentStore() {}
		~ComponentStore() {}

		inline bool add(const Entity entity, C&& component) {
			return mStore.insert(std::make_pair(entity, std::move(component))).second;
		}

		inline bool remove(Entity entity) {
			return (0 < mStore.erase(entity));
		}

		inline bool has(Entity entity) const {
			return (mStore.end() != mStore.find(entity));
		}

		inline C& get(Entity entity) {
			return mStore.at(entity);
		}

		inline C extract(Entity entity) {
			C component = std::move(mStore.at(entity));
			mStore.erase(entity);
			return component;
		}

		inline const std::unordered_map<Entity, C>& getComponents() {
			return mStore;
		}

	private:
		std::unordered_map<Entity, C> mStore;
		static const ComponentType type = C::type;
	};

}

#endif