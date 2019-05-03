/*! \file assetManager.h
 * \author Giovanni Aleman
 *
 ******************************************************************************
 Copyright (c) 2016-2019 Giovanni Aleman

 This Source Code Form is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ******************************************************************************
 */

#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/container/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include "FileLoader.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "SpriteSheet.h"
#include "Logger.h"

/*! \class AssetManager
 *  \brief Assists in loading assets into the game engine
 */
class AssetManager
{
private:
	boost::unordered::unordered_map<boost::container::string, boost::shared_ptr<MeshData>> meshes;
	boost::unordered::unordered_map<boost::container::string, boost::container::string> meshShortNames;
	boost::unordered::unordered_map<boost::container::string, boost::shared_ptr<Texture>> textures;
	boost::unordered::unordered_map<boost::container::string, boost::container::string> textureShortNames;
	boost::unordered::unordered_map<boost::container::string, boost::shared_ptr<Shader>> shaders;
	boost::unordered::unordered_map<boost::container::string, boost::container::string> shaderShortNames;
	boost::unordered::unordered_map<boost::container::string, boost::shared_ptr<ShaderProgram>> shaderPrograms;
	boost::unordered::unordered_map<boost::container::string, boost::shared_ptr<Material>> materials;
	boost::filesystem::path assetDir;
	void LoadDir(const boost::filesystem::path &path);
	void LoadAsset(const char* path, const char* ext, boost::container::string name);

public:
	AssetManager();
	AssetManager(const AssetManager&);
	void CreateMaterial(boost::container::string id, boost::shared_ptr<Texture> diff, boost::shared_ptr<Texture> norm, boost::shared_ptr<Texture> spec, boost::shared_ptr<ShaderProgram> program);
	boost::shared_ptr<MeshData> GetMesh(boost::container::string id) const;
	boost::shared_ptr<Texture> GetTexture(boost::container::string id) const;
	boost::shared_ptr<Shader> GetShader(boost::container::string id) const;
	boost::shared_ptr<ShaderProgram> GetShaderProgram(boost::container::string id) const;
	boost::shared_ptr<Material> GetMaterial(boost::container::string id) const;

	void SaveAssets();
	void SaveAssetToFile(const char* dir, const char* filename, const char* content);

	/*! \brief Sets the asset directory to used
	 *
	 * \param (boost::container::string) dir - The directory to use for assets
	 */
	inline void SetAssetDir(boost::container::string dir) { assetDir = boost::filesystem::path(dir.c_str()); };

	/*! \brief Loads the specified file / folder
	 *
	 * \param (char*) path - The path of the file or folder
	 */
	inline void LoadDirectory(const char* path) { LoadDir(boost::filesystem::path(path)); }
	void LoadAssetsFromAssetDir();
	void operator=(const AssetManager&);
	~AssetManager();
};

#endif
