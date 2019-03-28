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

#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include "FileLoader.h"
#include "Shader.h"
#include "Logger.h"

//Predefinied cause these don't exist yet
class Texture;

/*! \class AssetManager
 *  \brief Assists in loading assets into the game engine
 */
class AssetManager
{
private:
	boost::unordered::unordered_map<std::string, boost::shared_ptr<MeshData>> meshes;
	boost::unordered::unordered_map<std::string, std::string> meshShortNames;
	boost::unordered::unordered_map<std::string, boost::shared_ptr<Texture>> textures;
	boost::unordered::unordered_map<std::string, std::string> textureShortNames;
	boost::unordered::unordered_map<std::string, boost::shared_ptr<Shader>> shaders;
	boost::unordered::unordered_map<std::string, std::string> shaderShortNames;
	boost::filesystem::path assetDir;
	void LoadDir(const boost::filesystem::path &path);
	void LoadAsset(const char* path, const char* ext, std::string name);

public:
	AssetManager();
	AssetManager(const AssetManager&);
	boost::shared_ptr<MeshData> GetMesh(std::string id) const;
	boost::shared_ptr<Texture> GetTexture(std::string id) const;
	boost::shared_ptr<Shader> GetShader(std::string id) const;
	void SaveAssets();
	void SaveAssetToFile(const char* dir, const char* filename, const char* content);
	void SetAssetDir(std::string dir);

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
