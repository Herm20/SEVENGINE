/*! \file fileLoader.cpp
 * \author Giovanni Aleman
 *
 ******************************************************************************
 * Copyright (c) 2016-2019 Giovanni Aleman
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ******************************************************************************
 */
#include "FileLoader.h"
#include <stb/stb_image.h>

namespace FileLoader
{
	static void ProcessAINode(aiNode* node, const aiScene* scene, boost::container::vector<MeshData> &meshes);
};

/*! \brief Loads a mesh as meshdata
 *
 * \param (const char*) path - Path to the mesh file
 *
 * \return (boost::container::vector<MeshData>) Vector of all loaded MeshData
 */
boost::container::vector<MeshData> FileLoader::LoadMeshData(const char* path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_CalcTangentSpace |
												 aiProcess_Triangulate |
												 aiProcess_JoinIdenticalVertices|
												 aiProcess_SortByPType);


	boost::container::vector<MeshData> meshes;
	ProcessAINode(scene->mRootNode, scene, meshes);

	std::string msg = "'";
	msg.append(path);

	if(meshes.size() == 0) {
		msg.append("' failed to load!");
		Logger::Log(Logger::ERROR, msg.c_str());
		return meshes;
	}

	msg.append("' loaded successfully");
	Logger::Log(Logger::MSG, msg.c_str());
	return meshes;
}

/*! \brief Loads meshdata from a .mesh file
 *
 * \param (const char*) path - Path to the mesh file
 *
 * \return (MeshData) The loaded MeshData
 */
MeshData FileLoader::LoadQuickMeshData(const char* path)
{
	char* txt = nullptr;
	FileLoader::LoadText(path, txt);

	bool isInds = false;
	std::stringstream ss(txt);
	std::string tmp;
	boost::container::vector<Vertex> verts;
	boost::container::vector<u32> inds;

	while(ss >> tmp)
	{
		if(!isalpha(tmp[0]))
		{
			if(isInds)
			{
				inds.push_back(atoi(tmp.c_str()));
			}

			else
			{
				Vertex v;
				v.pos.x = atoi(tmp.c_str());
				ss >> v.pos.y >> v.pos.z;
				ss >> v.uv.x >> v.uv.y;
				ss >> v.norm.x >> v.norm.y >> v.norm.z;
				ss >> v.tan.x >> v.tan.y >> v.tan.z;
				ss >> v.bitan.x >> v.bitan.y >> v.bitan.z;

				verts.push_back(v);
			}
		}

		else if(tmp[0] == 'i')
		{
			isInds = true;
		}
	}

	FileLoader::DeleteText(txt);

	MeshData data;
	data.CopyVerticesFromVector(verts);
	data.CopyIndicesFromVector(inds);

	return data;
}

/*! \brief Converts an assimp scene to a series of meshes
 *
 * \param (aiNode*) node - The ai node to process
 * \param (const aiScene*) scene - The ai scene to gather info from
 * \param (boost::container::vector<MeshData> &) meshes - Vector to store the mesh data after processing
 */
void FileLoader::ProcessAINode(aiNode* node, const aiScene* scene, boost::container::vector<MeshData> &meshes)
{
	//Iterate through the submeshes
	for(u32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		boost::container::vector<Vertex> verts;
		boost::container::vector<u32> inds;
		bool uvs;

		//Get all the indices in the submesh
		for(u32 j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace face = mesh->mFaces[j];
			for(u32 k = 0; k < face.mNumIndices; k++)
				inds.push_back(face.mIndices[k]);
		}

		//Check if there are uvs
		if(mesh->mTextureCoords[0])
			uvs = true;

		//Iterate though all the vertices
		for(u32 j = 0; j < mesh->mNumVertices; j++)
		{
			Vertex v;
			v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
			v.norm = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
			v.tan = glm::vec3(mesh->mTangents[j].x, mesh->mTangents[j].y, mesh->mTangents[j].z);
			v.bitan = glm::vec3(mesh->mBitangents[j].x, mesh->mBitangents[j].y, mesh->mBitangents[j].z);

			if(uvs)
				v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			else
				v.uv = glm::vec2(0.0f, 0.0f);

			verts.push_back(v);
		}

		//Set the mesh data and push it
		MeshData data;
		data.CopyVerticesFromVector(verts);
		data.CopyIndicesFromVector(inds);
		meshes.push_back(data);
	}

	//Iterate through all the children
	for(u32 i = 0; i < node->mNumChildren; i++)
	{
		ProcessAINode(node->mChildren[i], scene, meshes);
	}
}

/*! \brief Loads a texture
 *
 * \param (const char*) path - Path to the texture
 * \param (unsigned char* &) data - The variable to store the data in
 * \param (i32*) width - The variable to store the width of the texture
 * \param (i32*) height - The variable to store the height of the texture
 * \param (i32*) channels - The variable to store the channels of the texture
 */
void FileLoader::LoadTexture(const char* path, unsigned char* &data, i32* width, i32* height, i32* channels)
{
	data = stbi_load(path, width, height, channels, 0);

	std::string msg = "'";
	msg.append(path);

	if(data == nullptr) {
		msg.append("' failed to load!");
		Logger::Log(Logger::ERROR, msg.c_str());
		return;
	}

	msg.append("' loaded successfully");
	Logger::Log(Logger::MSG, msg.c_str());
}

/*! \brief Deletes texture data
 *
 * \param (unsigned char* &) data - The data to delete
 */
void FileLoader::DeleteTexture(unsigned char* &data)
{
	stbi_image_free(data);
}

/*! \brief Loads an HDR texture
 *
 * \param (const char*) path - Path to the HDR texture
 * \param (float* &) data - The variable to store the data in
 * \param (i32*) width - The variable to store the width of the texture
 * \param (i32*) height - The variable to store the height of the texture
 * \param (i32*) channels - The variable to store the channels of the texture
 */
void FileLoader::LoadTextureHDR(const char* path, float* &data, i32* width, i32* height, i32* channels)
{
	data = stbi_loadf(path, width, height, channels, 0);

	std::string msg = "'";
	msg.append(path);

	if(data == nullptr) {
		msg.append("' failed to load!");
		Logger::Log(Logger::ERROR, msg.c_str());
		return;
	}

	msg.append("' loaded successfully");
	Logger::Log(Logger::MSG, msg.c_str());
}

/*! \brief Deletes texture data
 *
 * \param (float* &) data - The data to delete
 */
void FileLoader::DeleteTextureHDR(float* &data)
{
	stbi_image_free(data);
}

/*! \brief Loads a file as text
 *
 * \param (const char*) path - Path to the file
 * \param (char* &) data - The variable to store the data in
 */
void FileLoader::LoadText(const char* path, char* &data)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	file.open(path, std::ios::in);

	std::string msg = "'";
	msg.append(path);

	if(!file.is_open()) {
		file.clear();
		msg.append("' failed to load!");
		Logger::Log(Logger::ERROR, msg.c_str());
		return;
	}

	file.seekg(0, file.end);
	size_t size = file.tellg();
	file.seekg(0, file.beg);

	data = new char[size + 1];
	file.read(data, size);
	data[size] = 0;
	file.close();

	msg.append("' loaded successfully");
	Logger::Log(Logger::MSG, msg.c_str());
}

/*! \brief Deletes text data
 *
 * \param (char* &) data - The data to delete
 */
void FileLoader::DeleteText(char* &data)
{
	delete [] data;
}
