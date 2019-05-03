#include "Texture.h"

Texture::Texture(i32 width, i32 height, i32 channels, uint32_t textureType, uint32_t dataType, const void* data) :
	textureType(textureType),
	width(width),
	height(height),
	channels(channels)
{
	u32 iFormat = (dataType == GL_UNSIGNED_BYTE) ? GL_RGBA8 : GL_RGBA16F;

	glGenTextures(1, &textureId);
	glBindTexture(this->textureType, textureId);
	glTexParameteri(this->textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(this->textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(this->textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(this->textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(this->textureType, 0, iFormat, this->width, this->height, 0, GL_RGBA, dataType, data);
	glGenerateMipmap(this->textureType);
	glBindTexture(this->textureType, 0);
}

Texture::Texture(const Texture &t)
{
	this->textureType = t.textureType;
	this->width = t.width;
	this->height = t.height;
	this->channels = t.channels;
	this->textureId = t.textureId;
}

void Texture::bind(u32 bindPoint)
{
	glActiveTexture(GL_TEXTURE0 + bindPoint);
	glBindTexture(textureType, this->textureId);
}

void Texture::unbind(u32 bindPoint)
{
	glActiveTexture(GL_TEXTURE0 + bindPoint);
	glBindTexture(textureType, 0);
}

const Texture & Texture::operator=(const Texture &t)
{
	this->textureType = t.textureType;
	this->width = t.width;
	this->height = t.height;
	this->channels = t.channels;
	this->textureId = t.textureId;

	return *this;
}

i32 Texture::GetWidth()
{
	return width;
}

i32 Texture::GetHeight()
{
	return height;
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureId);
}