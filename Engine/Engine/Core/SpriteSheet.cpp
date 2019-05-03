#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
{

}

void SpriteSheet::Generate(glm::uvec2 cellSize, boost::shared_ptr<Texture> diff)
{
	int totalFrames_w = diff->GetWidth() / cellSize.x;
	int totalFrames_h = diff->GetHeight() / cellSize.y;

	glm::vec2 wh(diff->GetWidth(), diff->GetHeight());

	scaleSize = glm::vec2(cellSize) / wh;

	for (int i = totalFrames_h; i >= 0; i--)
	{
		for (int j = 0; j <= totalFrames_w; j++)
		{
			if (j != totalFrames_w) 
			{
				offsets.push_back((glm::vec2(j, i) * glm::vec2(cellSize)) / wh);
			}
		}
	}

}

SpriteSheet::~SpriteSheet()
{

}