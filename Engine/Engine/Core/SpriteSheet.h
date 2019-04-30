#ifndef  SPRITESHEET_H_
#define SPRITESHEET_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include "Texture.h"
#include "Animation.h"

class SpriteSheet
{
public:
	SpriteSheet();
	void Generate(glm::uvec2 cellSize, boost::shared_ptr<Texture> diff);
	~SpriteSheet();
	glm::vec2 scaleSize;
	boost::container::vector<glm::vec2> offsets;
	int currFrame;
private:
	
};
#endif // ! SPRITESHEET_H_
