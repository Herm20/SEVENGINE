/*! \file assetManager.cpp
 * \author Giovanni Aleman
 *
 ******************************************************************************
 Copyright (c) 2016-2019 Giovanni Aleman

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ******************************************************************************
 */

#include "AssetManager.h"

/*! \brief Asset loader constructor
 */
AssetManager::AssetManager()
{

}

/*! \brief Gets the mesh with the specified id
 *
 * \param (std::string) id - The id of the mesh in the map
 *
 * \return (boost::shared_ptr<MeshData>) Pointer to the retrieved mesh
 */
boost::shared_ptr<Mesh> AssetManager::GetMesh(std::string id) const
{
	if(this->meshes.find(id) != this->meshes.end())
		return this->meshes.find(id)->second;

	return nullptr;
}

/*! \brief Gets the texture with the specified id
 *
 * \param (std::string) id - The id of the texture in the map
 *
 * \return (boost::shared_ptr<Texture>) Pointer to the retrieved texture
 */
//boost::shared_ptr<Texture> AssetManager::GetTexture(std::string id)
//{
//	if(AssetManager::loadedTextures.find(id) != AssetManager::loadedTextures.end())
//		return AssetManager::loadedTextures[id];
//
//	return nullptr;
//}

/*! \brief Gets the shader with the specified id
 *
 * \param (std::string) id - The id of the shader in the map
 *
 * \return (boost::shared_ptr<Shader>) Pointer to the retrieved shader
 */
boost::shared_ptr<Shader> AssetManager::GetShader(std::string id) const
{
	 if(this->shaders.find(id) != this->shaders.end())
		return this->shaders.find(id)->second;

	return nullptr;
}

/*! \brief Loads selected file and puts it in the right map
 *
 * \param (const char*) path - The path of the file
 * \param (const char*) ext - The extension of the loaded file
 * \param (std::string) name - The name that will be used to store it in the map
 */
void AssetManager::LoadAsset(const char* path, const char* ext, std::string name)
{
	//Mesh files
	if(strcmp(ext, ".obj") == 0 || strcmp(ext, ".fbx") == 0 || strcmp(ext, ".dae") == 0)
	{
		if(this->meshes.find(name) == this->meshes.end())
		{
			boost::container::vector<Mesh> meshData = FileLoader::LoadMeshData(path);

			for(u32 i = 0; i < meshData.size(); i++)
			{
				//TODO: Change the name so multiple meshes don't overwrite each other
				std::string modName = name;

				if(i > 0)
					modName += std::to_string(i);

				meshes[name] = boost::shared_ptr<Mesh>(new Mesh(meshData[i]));
			}
		}
	}

	//Texture files
	else if(strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0 ||
		    strcmp(ext, ".tga") == 0 || strcmp(ext, ".hdr") == 0)
	{
		if(this->textures.find(name) == this->textures.end())
		{
			i32 width;
			i32 height;
			i32 channels;

			if(strcmp(ext, ".hdr") == 0)
			{
				float* data;
				//float* data = nullptr;
				FileLoader::LoadTextureHDR(path, data, &width, &height, &channels);

				//TODO: Create a new texture with the data

				FileLoader::DeleteTextureHDR(data);
			}

			else
			{
				unsigned char* data;
				//unsigned char* data = nullptr;
				FileLoader::LoadTexture(path, data, &width, &height, &channels);
				//TODO: Create a new texture with the data

				FileLoader::DeleteTexture(data);
			}

		}
	}

	else if(strcmp(ext, ".txt") == 0)
	{
		char* txt = nullptr;
		FileLoader::LoadText(path, txt);

		//TODO: More specific stuff later

		FileLoader::DeleteText(txt);
	}

	//Other text files
	else if(strcmp(ext, ".vert") == 0 || strcmp(ext, ".frag") == 0 || strcmp(ext, ".tese") == 0 ||
			strcmp(ext, ".tesc") == 0 || strcmp(ext, ".geom") == 0 || strcmp(ext, ".comp") == 0)
	{
		GLenum type = GL_VERTEX_SHADER;
		char* txt = nullptr;
		FileLoader::LoadText(path, txt);

		if(strcmp(ext, ".tesc") == 0)
			type = GL_TESS_CONTROL_SHADER;
		else if(strcmp(ext, ".tese") == 0)
			type = GL_TESS_EVALUATION_SHADER;
		else if(strcmp(ext, ".geom") == 0)
			type = GL_GEOMETRY_SHADER;
		else if(strcmp(ext, ".frag") == 0)
			type = GL_FRAGMENT_SHADER;
		else if(strcmp(ext, ".comp") == 0)
			type = GL_COMPUTE_SHADER;

		shaders[name] = boost::shared_ptr<Shader>(new Shader(txt, type));
		FileLoader::DeleteText(txt);
	}
}

/*! \brief Function to actually load the files
 */
void AssetManager::LoadDir(const boost::filesystem::path &path)
{
	if(!boost::filesystem::exists(path)) {
		//printf("Directory not found");
		return;
	}

	for(boost::filesystem::directory_iterator it(path); it != boost::filesystem::directory_iterator(); it++)
	{
		if(boost::filesystem::is_directory(it->status()))
			LoadDir(it->path());
		else
		{
			if(it->path().has_extension() && it->path().has_filename())
			{
				LoadAsset(it->path().string().c_str(), it->path().extension().string().c_str(), it->path().stem().string());
			}
		}
	}

}

/*! \brief Asset loader destructor
 */
AssetManager::~AssetManager()
{

}