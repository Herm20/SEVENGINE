#ifndef SPRITESHEETSYSTEM_H_
#define SPRITESHEETSYSTEM_H_

#include <glm/glm.hpp>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
#include "../ECS/System.h"
#include "../SpriteSheet.h"

class SpriteSheetSystem : public ecs::System
{
public:
	explicit SpriteSheetSystem(ecs::Manager& manager);
	~SpriteSheetSystem();

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;
};

#endif