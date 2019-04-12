#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ComponentType.h"

namespace ecs {

	struct Component {
		static const ComponentType type = _invalidComponentType;
	};

}

#endif
