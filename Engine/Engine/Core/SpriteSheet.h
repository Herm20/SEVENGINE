#ifndef  SPRITESHEET_H_
#define SPRITESHEET_H_

#define GLM_ENABLE_EXPERIMENTAL

#include "Material.h"
#include <glm/glm.hpp>

class SpriteSheet : public Material
{
public:
	SpriteSheet(int cellWidth, int cellHeight);
	~SpriteSheet();
	void GenerateFrames();

private:
	glm::vec2 scaleSize;
	glm::vec2 frames[];
};
#endif // ! SPRITESHEET_H_
