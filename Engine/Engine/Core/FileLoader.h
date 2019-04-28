#ifndef FILELOADER_H_
#define FILELOADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Logger.h"
#include "Types.h"
#include "MeshData.h"
#include "Mesh.h"

/*! \namespace FileLoader
 *  \brief File loading methods
 */
namespace FileLoader
{
	void SetLoaderProperties();
	boost::shared_ptr<MeshData> LoadQuickMeshData(const char* path);
	boost::shared_ptr<MeshData> LoadMeshData(const char* path);
	void LoadTexture(const char* path, unsigned char* &data, i32* width, i32* height, i32* channels);
	void DeleteTexture(unsigned char* &data);
	void LoadTextureHDR(const char* path, float* &data, int32_t* width, int32_t* height, int32_t* channels);
	void DeleteTextureHDR(float* &data);
	void LoadText(const char* path, char* &data);
	void DeleteText(char* &data);
};

#endif