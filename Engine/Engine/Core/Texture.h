#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include "Types.h"

/*! \class Texture
 *  \brief An OpenGL texture
 */
class Texture
{
private:
	u32 textureId;
	u32 textureType;
	i32 width;
	i32 height;
	i32 channels;

public:
	Texture(i32 width, i32 height, i32 channels, uint32_t textureType, uint32_t dataType, const void* data);
	Texture(const Texture &t);
	void bind(u32 bindPoint);
	void unbind(u32 bindPoint);
	const Texture & operator=(const Texture &t);
	i32 GetWidth();
	i32 GetHeight();
	~Texture();
};

#endif