#include "LightSystem.h"

#include "../ECS/Component.h"
#include "../ECS/Manager.h"

LightSystem::LightSystem(ecs::Manager& manager) : ecs::System(manager)
{
	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::LightComponent::_mType);
	requiredComponents.insert(ecs::TransformComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));
}


LightSystem::~LightSystem()
{

}

void LightSystem::startFrame(float dt)
{
	rendererLightsVec->clear();
}

void LightSystem::updateEntity(float dt, ecs::Entity entity)
{
	ecs::LightComponent & light = manager.getComponentStore<ecs::LightComponent>().get(entity);
	ecs::TransformComponent & transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);

	light.light.pos = transform.transform.GetPosition();
	light.light.dir = transform.transform.ForwardVector();

	if(rendererLightsVec->size() < 16)
		rendererLightsVec->push_back(light.light);
}

void LightSystem::endFrame(float dt)
{

}
