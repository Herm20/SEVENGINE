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
#include <cstdio>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>
#include "FileLoader.h"

//Predefinied cause these don't exist yet
class Mesh;
class Texture;

/*! \class AssetManager
 *  \brief Assists in loading assets into the game engine
 */
class AssetManager
{
private:
	boost::unordered::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
	boost::unordered::unordered_map<std::string, std::shared_ptr<Texture>> textures;
	void LoadDir(const boost::filesystem::path &path);

public:
	AssetManager();
	AssetManager(const AssetManager&);
	std::shared_ptr<Mesh> GetMesh(const char* id);
	std::shared_ptr<Texture> GetTexture(const char* id);
	//void SaveAssets();
	void LoadAsset(const char* path, const char* ext, std::string name);
	void LoadDirectory(const char* path);
	void operator=(const AssetManager&);
	~AssetManager();
};

#endif
