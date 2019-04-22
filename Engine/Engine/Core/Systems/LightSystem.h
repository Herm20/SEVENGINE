#ifndef LIGHTSYSTEM_H_
#define LIGHTSYSTEM_H_

#include <glm/glm.hpp>
#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>
#include "../ECS/System.h"
#include "../Light.h"

class LightSystem : public ecs::System
{
private:
	boost::container::vector<Light>* rendererLightsVec;

public:
	explicit LightSystem(ecs::Manager& manager);
	~LightSystem();

	inline void SetLightsVector(boost::container::vector<Light>* lightsVec) { this->rendererLightsVec = lightsVec; }

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;
};

#endif

