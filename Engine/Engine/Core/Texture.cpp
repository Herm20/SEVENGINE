#include "Texture.h"
#include <iostream>


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, textID);
}

void Texture::Load()
{
	FIBITMAP* Image = FreeImage_Load(FreeImage_GetFileType(fileName.c_str(), 0), fileName.c_str());

	if (Image == nullptr)
	{
		textID = -1;
	}
	else
	{
		FIBITMAP* Image32Bit = FreeImage_ConvertTo32Bits(Image);

		FreeImage_Unload(Image);

		glGenTextures(1, &textID);

		glBindTexture(GL_TEXTURE_2D, textID);

		unsigned int width = FreeImage_GetWidth(Image32Bit);
		unsigned int height = FreeImage_GetHeight(Image32Bit);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(Image32Bit));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		FreeImage_Unload(Image32Bit);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

}



void Texture::Unload()
{
	glDeleteTextures(1, &textID);
}
