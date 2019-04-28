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
	static void ProcessAINode(aiNode* node, const aiScene* scene, boost::container::vector<Vertex> &verts, boost::container::vector<u32> &inds, boost::container::vector<u32> &offsets, boost::container::vector<u32> &amounts, u32 baseOffset);
};

/*! \brief Sets up properties for file loaders
 */
void FileLoader::SetLoaderProperties()
{
	stbi_set_flip_vertically_on_load(true);
}

/*! \brief Loads a mesh as meshdata
 *
 * \param (const char*) path - Path to the mesh file
 *
 * \return (boost::shared_ptr<MeshData>) The loaded MeshData
 */
boost::shared_ptr<MeshData> FileLoader::LoadMeshData(const char* path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_CalcTangentSpace |
												 aiProcess_Triangulate |
												 aiProcess_JoinIdenticalVertices|
												 aiProcess_SortByPType |
												 aiProcess_GenNormals |
												 aiProcess_FixInfacingNormals );

	boost::container::vector<Vertex> verts;
	boost::container::vector<u32> inds;
	boost::container::vector<u32> offsets;
	boost::container::vector<u32> amounts;

	ProcessAINode(scene->mRootNode, scene, verts, inds, offsets, amounts, 0);

	//Set the mesh data and push it
	boost::shared_ptr<MeshData> data = boost::shared_ptr<MeshData>(new MeshData());
	data->CopyVerticesFromVector(verts);
	data->CopyIndicesFromVector(inds);
	data->CopyIndOffsetsFromVector(offsets);
	data->CopyIndAmountsFromVector(amounts);

	boost::container::string msg = "'";
	msg.append(path);

	if(data->GetVertexCount() == 0) {
		msg.append("' failed to load!");
		Logger::Log(Logger::ERROR, msg.c_str());
		return nullptr;
	}

	msg.append("' loaded successfully");
	Logger::Log(Logger::MSG, msg.c_str());
	return data;
}

/*! \brief Loads meshdata from a .mesh file
 *
 * \param (const char*) path - Path to the mesh file
 *
 * \return (boost::shared_ptr<MeshData>) The loaded MeshData
 */
boost::shared_ptr<MeshData> FileLoader::LoadQuickMeshData(const char* path)
{
	/*FILE* file;
	file = fopen(path, "r");

	int flags = 0;
	boost::container::vector<Vertex> verts;
	boost::container::vector<u32> inds;
	boost::container::vector<u32> offsets;
	boost::container::vector<u32> amounts;

	boost::shared_ptr<MeshData> meshData = boost::shared_ptr<MeshData>(new MeshData());

	glm::uvec4 size;

	fscanf(file, "%d %d %d %d\n", &size.x, &size.y, &size.z, &size.w);

	verts.reserve(size.x);
	inds.reserve(size.y);
	offsets.reserve(size.z);
	amounts.reserve(size.w);

	char tmp;
	Vertex v;
	u32 i;
	fpos_t pos;

	while(!feof(file))
	{
		fgetpos(file, &pos);
		fscanf(file, "%c", &tmp);

		if(!isalpha(tmp))
		{
			fsetpos(file, &pos);
			/*switch(flags)
			{
				case 1:
					fscanf(file, "%d\n", &i);
					inds.push_back(i);
					break;
				case 2:
					fscanf(file, "%d\n", &i);
					offsets.push_back(i);
					break;
				case 3:
					fscanf(file, "%d\n", &i);
					amounts.push_back(i);
					break;
				default:
					fscanf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &v.pos.x, &v.pos.y, &v.pos.z, &v.uv.x, &v.uv.y, &v.norm.x, &v.norm.y, &v.norm.z, &v.tan.x, &v.tan.y, &v.tan.z, &v.bitan.x, &v.bitan.y,& v.bitan.z);
					verts.push_back(v);
					break;
			}
		}

		else if(tmp == 'i')
		{
			flags = 1;
			fscanf(file, "\n");
		}

		else if(tmp == 'o')
		{
			flags = 2;
			fscanf(file, "\n");
		}

		else if(tmp == 'a')
		{
			flags = 3;
			fscanf(file, "\n");
		}
	}
	fclose(file);

	meshData->CopyVerticesFromVector(verts);
	meshData->CopyIndicesFromVector(inds);
	meshData->CopyIndOffsetsFromVector(offsets);
	meshData->CopyIndAmountsFromVector(amounts);

	return meshData;*/
	return nullptr;
}

/*! \brief Converts an assimp scene to a series of meshes
 *
 * \param (aiNode*) node - The ai node to process
 * \param (const aiScene*) scene - The ai scene to gather info from
 * \param (boost::shared_ptr<Vertex> &) verts - Vector to store the vertex data
 * \param (boost::shared_ptr<u32> &) inds - Vector to store the index data
 * \param (boost::shared_ptr<u32> &) offsets - Vector to store the index offset data
 * \param (boost::shared_ptr<u32> &) amounts - Vector to store the index amount data
 * \param (u32) baseOffset - The base offset for the index offsets
 */
void FileLoader::ProcessAINode(aiNode* node, const aiScene* scene, boost::container::vector<Vertex> &verts, boost::container::vector<u32> &inds, boost::container::vector<u32> &offsets, boost::container::vector<u32> &amounts, u32 baseOffset)
{
	//Iterate through the submeshes
	for(u32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		bool uvs = false;
		bool norms = false;
		bool tansBitans = false;

		offsets.push_back(inds.size());

		u32 indAmount = 0;
		//Get all the indices in the submesh
		for(u32 j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace face = mesh->mFaces[j];
			indAmount += face.mNumIndices;
			for(u32 k = 0; k < face.mNumIndices; k++) {
				inds.push_back(face.mIndices[k] + verts.size());
			}
		}

		amounts.push_back(indAmount);

		//Check if there are uvs
		if(mesh->HasTextureCoords(0))
			uvs = true;
		if(mesh->HasNormals())
			norms = true;
		if(mesh->HasTangentsAndBitangents())
			tansBitans = true;

		//Iterate though all the vertices
		for(u32 j = 0; j < mesh->mNumVertices; j++)
		{
			Vertex v;
			v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

			if(uvs)
				v.uv = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			else
				v.uv = glm::vec2();

			if(norms)
				v.norm = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
			else
				v.norm = glm::vec3();

			if(tansBitans)
			{
				v.tan = glm::vec3(mesh->mTangents[j].x, mesh->mTangents[j].y, mesh->mTangents[j].z);
				v.bitan = glm::vec3(mesh->mBitangents[j].x, mesh->mBitangents[j].y, mesh->mBitangents[j].z);
			}

			else
			{
				v.tan = glm::vec3();
				v.bitan = glm::vec3();
			}

			verts.push_back(v);
		}
	}

	//Iterate through all the children
	for(u32 i = 0; i < node->mNumChildren; i++)
	{
		ProcessAINode(node->mChildren[i], scene, verts, inds, offsets, amounts, verts.size());
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

	boost::container::string msg = "'";
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

	boost::container::string msg = "'";
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

	file.open(path, std::ios::binary);

	boost::container::string msg = "'";
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
	std::fill(data, data + sizeof(char) * (size + 1), 0);
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
