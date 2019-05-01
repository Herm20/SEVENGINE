#include "SpriteSheetSystem.h"

#include "../ECS/Component.h"
#include "../ECS/Manager.h"

SpriteSheetSystem::SpriteSheetSystem(ecs::Manager& manager) : ecs::System(manager)
{
	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::MeshRendererComponent::_mType);
	requiredComponents.insert(ecs::SpriteSheetComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));
}


SpriteSheetSystem::~SpriteSheetSystem()
{

}

void SpriteSheetSystem::startFrame(float dt)
{
	
}

void SpriteSheetSystem::updateEntity(float dt, ecs::Entity entity)
{
	ecs::MeshRendererComponent & mesh = manager.getComponentStore<ecs::MeshRendererComponent>().get(entity);
	ecs::SpriteSheetComponent & ss = manager.getComponentStore<ecs::SpriteSheetComponent>().get(entity);

	ss.currFrameTime += Timer::GetDeltaTime();

	Animation anim = ss.animations["idle"];

	if (!ss.frameSet)
	{
		ss.ss.currFrame = anim.startFrame;
		ss.frameSet = true;
	}

	while (ss.currFrameTime >= anim.animRate)
	{
		if (ss.ss.currFrame != anim.endFrame || anim.doesLoop) 
		{
			ss.ss.currFrame++;
		}
		printf("%i ", ss.ss.currFrame);
		ss.currFrameTime -= anim.animRate;

		if (ss.ss.currFrame > anim.endFrame)
		{
			ss.ss.currFrame = anim.startFrame;
		}
	}

	mesh.material->SetUVOffset(ss.ss.offsets[ss.ss.currFrame]);
	mesh.material->SetUVSize(ss.ss.scaleSize);
}

void SpriteSheetSystem::endFrame(float dt)
{

}
