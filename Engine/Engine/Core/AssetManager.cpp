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
	u8 diffuse[3] = { 255, 255, 255 }; //1px, 3 channel white texture
	u8 normal[3] = { 128, 128, 255 }; //1px, 3 channel half red, half green, full blue texture

	this->textureShortNames["defaultAlbedo"] = "defaultAlbedo";
	this->textures["defaultAlbedo"] = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)diffuse));
	this->textureShortNames["defaultNormal"] = "defaultNormal";
	this->textures["defaultNormal"] = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)normal));
	this->textureShortNames["defaultSpecular"] = "defaultSpecular";
	this->textures["defaultSpecular"] = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)diffuse));

	FileLoader::SetLoaderProperties();
}

/*! \brief Creates a material with the parameters and puts it in the map
 *
 * \param (boost::container::string) id - The id for the material
 * \param (boost::shared_ptr<Texture>) diffuseTex - The diffuse tex
 * \param (boost::shared_ptr<Texture>) normalTex - The normal tex
 * \param (boost::shared_ptr<Texture>) specularTex - The specular tex
 * \param (boost::shared_ptr<ShaderProgram>) program - The shader program
 */
void AssetManager::CreateMaterial(boost::container::string id, boost::shared_ptr<Texture> diff, boost::shared_ptr<Texture> norm, boost::shared_ptr<Texture> spec, boost::shared_ptr<ShaderProgram> program)
{
	this->materials[id] = boost::shared_ptr<Material>(new Material(diff, norm, spec, program));
}

/*! \brief Gets the mesh with the specified id
 *
 * \param (boost::container::string) id - The id of the mesh in the map
 *
 * \return (boost::shared_ptr<MeshData>) Pointer to the retrieved mesh
 */
boost::shared_ptr<MeshData> AssetManager::GetMesh(boost::container::string id) const
{
	if(this->meshShortNames.find(id) != this->meshShortNames.end())
	{
		if(this->meshes.find(this->meshShortNames.find(id)->second) != this->meshes.end())
			return this->meshes.find(this->meshShortNames.find(id)->second)->second;
	}

	boost::container::string msg = "Asset with ID '";
	msg += id;
	msg += "' not found";
	Logger::Log(Logger::ERROR, msg.c_str());

	return nullptr;
}

/*! \brief Gets the texture with the specified id
 *
 * \param (boost::container::string) id - The id of the texture in the map
 *
 * \return (boost::shared_ptr<Texture>) Pointer to the retrieved texture
 */
boost::shared_ptr<Texture> AssetManager::GetTexture(boost::container::string id) const
{
	if(this->textureShortNames.find(id) != this->textureShortNames.end())
	{
		if(this->textures.find(this->textureShortNames.find(id)->second) != this->textures.end())
			return this->textures.find(this->textureShortNames.find(id)->second)->second;
	}

	boost::container::string msg = "Asset with ID '";
	msg += id;
	msg += "' not found";
	Logger::Log(Logger::ERROR, msg.c_str());

	return this->textures.find("defaultAlbedo")->second;
}

/*! \brief Gets the shader with the specified id
 *
 * \param (boost::container::string) id - The id of the shader in the map
 *
 * \return (boost::shared_ptr<Shader>) Pointer to the retrieved shader
 */
boost::shared_ptr<Shader> AssetManager::GetShader(boost::container::string id) const
{
	if(this->shaderShortNames.find(id) != this->shaderShortNames.end())
	{
		if(this->shaders.find(this->shaderShortNames.find(id)->second) != this->shaders.end())
			return this->shaders.find(this->shaderShortNames.find(id)->second)->second;
	}

	boost::container::string msg = "Asset with ID '";
	msg += id;
	msg += "' not found";
	Logger::Log(Logger::ERROR, msg.c_str());

	return nullptr;
}

/*! \brief Gets the shader program with the specified id
 *
 * \param (boost::container::string) id - The id of the shader program in the map
 *
 * \return (boost::shared_ptr<ShaderProgram>) Pointer to the retrieved shader program
 */
boost::shared_ptr<ShaderProgram> AssetManager::GetShaderProgram(boost::container::string id) const
{
	if(this->shaderPrograms.find(id) != this->shaderPrograms.end())
		return this->shaderPrograms.find(id)->second;

	boost::container::string msg = "Asset with ID '";
	msg += id;
	msg += "' not found";
	Logger::Log(Logger::ERROR, msg.c_str());

	return nullptr;
}

/*! \brief Gets the material with the specified id
 *
 * \param (boost::container::string) id - The id of the material in the map
 *
 * \return (boost::shared_ptr<Material>) Pointer to the retrieved material
 */
boost::shared_ptr<Material> AssetManager::GetMaterial(boost::container::string id) const
{
	if(this->materials.find(id) != this->materials.end())
		return this->materials.find(id)->second;

	boost::container::string msg = "Asset with ID '";
	msg += id;
	msg += "' not found";
	Logger::Log(Logger::ERROR, msg.c_str());

	return nullptr;
}

/*! \brief Loads selected file and puts it in the right map
 *
 * \param (const char*) path - The path of the file
 * \param (const char*) ext - The extension of the loaded file
 * \param (boost::container::string) name - The name that will be used to store it in the map
 */
void AssetManager::LoadAsset(const char* path, const char* ext, boost::container::string name)
{
	//Mesh files
	if(strcmp(ext, ".obj") == 0 || strcmp(ext, ".fbx") == 0 || strcmp(ext, ".dae") == 0 || strcmp(ext, ".blend") == 0)
	{
		if(this->meshes.find(name) == this->meshes.end())
		{
			boost::filesystem::path meshFile(path);
			//meshFile.replace_extension(boost::filesystem::path(".mesh"));
   //
			//if(boost::filesystem::exists(meshFile))
			//{
			//	boost::shared_ptr<MeshData> meshData = FileLoader::LoadQuickMeshData(meshFile.string().c_str());
			//	meshShortNames[name] = path;
			//	meshes[path] = boost::shared_ptr<MeshData>(meshData);
			//}

			//else
			//{
				boost::shared_ptr<MeshData> meshData = FileLoader::LoadMeshData(path);
				meshShortNames[name] = path;
				meshes[path] = boost::shared_ptr<MeshData>(meshData);
			//}
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
				float* data = nullptr;
				FileLoader::LoadTextureHDR(path, data, &width, &height, &channels);

				textureShortNames[name] = path;
				textures[path] = boost::shared_ptr<Texture>(new Texture(width, height, channels, GL_TEXTURE_2D, GL_FLOAT, (const void*)data));
				FileLoader::DeleteTextureHDR(data);
			}

			else
			{
				unsigned char* data = nullptr;
				FileLoader::LoadTexture(path, data, &width, &height, &channels);
				textureShortNames[name] = path;
				textures[path] = boost::shared_ptr<Texture>(new Texture(width, height, channels, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)data));
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

		shaderShortNames[name] = path;
		shaders[path] = boost::shared_ptr<Shader>(new Shader(txt, type));
		FileLoader::DeleteText(txt);
	}
}

/*! \brief Saves all assets to the asset directory
 */
void AssetManager::SaveAssets()
{
	//for(auto it = meshes.begin(); it != meshes.end(); it++)
	//{
	//	boost::filesystem::path path(it->first);
 //
	//	if(strcmp(path.extension().string().c_str(), ".mesh") != 0)
	//		path.replace_extension(boost::filesystem::path(".mesh"));
 //
	//	if(!boost::filesystem::exists(path))
	//	{
	//		boost::container::string fileContents = "";
	//		boost::shared_ptr<MeshData> data = it->second;
 //
	//		fileContents.reserve((data->GetVertexCount() * 8) + (data->GetVertexCount() + data->GetIndexCount() + data->GetIndOffsetCount() + data->GetIndAmountCount() + 7) * 2 + 1);
 //
	//		fileContents += to_string(data->GetVertexCount());
	//		fileContents += " ";
	//		fileContents += to_string(data->GetIndexCount());
	//		fileContents += " ";
	//		fileContents += to_string(data->GetIndOffsetCount());
	//		fileContents += " ";
	//		fileContents += to_string(data->GetIndAmountCount());
	//		fileContents += '\n';
 //
	//		for(u32 i = 0; i < data->GetVertexCount(); i++)
	//		{
	//			fileContents += to_string(data->GetVertices()[i].pos.x);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].pos.y);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].pos.z);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].uv.x);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].uv.y);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].norm.x);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].norm.y);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].norm.z);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].tan.x);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].tan.y);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].tan.z);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].bitan.x);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].bitan.y);
	//			fileContents += " ";
	//			fileContents += to_string(data->GetVertices()[i].bitan.z);
	//			fileContents += "\n";
	//		}
 //
	//		fileContents += "\ni\n";
 //
	//		for(u32 i = 0; i < data->GetIndexCount(); i++)
	//		{
	//			fileContents += to_string(data->GetIndices()[i]);
	//			fileContents += "\n";
	//		}
 //
	//		fileContents += "\no\n";
 //
	//		for(u32 i = 0; i < data->GetIndOffsetCount(); i++)
	//		{
	//			fileContents += to_string(data->GetIndOffsets()[i]);
	//			fileContents += "\n";
	//		}
 //
	//		fileContents += "\na\n";
 //
	//		for(u32 i = 0; i < data->GetIndAmountCount(); i++)
	//		{
	//			fileContents += to_string(data->GetIndAmounts()[i]);
	//			fileContents += "\n ";
	//		}
 //
	//		SaveAssetToFile(path.parent_path().string().c_str(), path.filename().string().c_str(), fileContents.c_str());
	//	}
	//}

	//TODO: Save other assets maybe
}

/*! \brief Saves an asset to a file
 *
 * \param (const char*) dir - The directory to save the file in
 * \param (const char*) filename - The name for the file (including the extension)
 * \param (const char*) content - The content of the file
 */
void AssetManager::SaveAssetToFile(const char* dir, const char* filename, const char* content)
{
	boost::filesystem::path path(dir);

	if(!boost::filesystem::exists(path))
	{
		if(boost::filesystem::create_directory(path))
		{
			boost::container::string msg = "Directory '";
			msg.append(path.string().c_str());
			msg.append("' created Successfully");
			Logger::Log(Logger::MSG, msg.c_str());
		}

		else
		{
			boost::container::string msg = "Failed to created directory '";
			msg.append(path.string().c_str());
			msg.append("'!");
			Logger::Log(Logger::ERROR, msg.c_str());
			return;
		}
	}

	if(boost::filesystem::is_directory(path))
	{
		ofstream file;
		file.open(path.append(filename).c_str());
		file << content;
		file.close();

		boost::container::string out = "'";
		out += path.string().c_str();
		out += "' written successfully";
		Logger::Log(Logger::MSG, out.c_str());
	}
}

/*! \brief Function to actually load the files
 */
void AssetManager::LoadDir(const boost::filesystem::path &path)
{
	if(!boost::filesystem::exists(path))
	{
		boost::container::string msg = "Directory '";
		msg.append(path.string().c_str());
		msg.append("' not found!");
		Logger::Log(Logger::ERROR, msg.c_str());
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
#ifdef _WIN64
				// TODO : Don't do this here please
				// PS : This should not work - yes it should
				boost::container::wstring wstr(it->path().stem().c_str());
				boost::container::string nstr;

				for (u64 i = 0; i < wstr.size(); ++i)
				{
					nstr += wstr[i];
				}

				LoadAsset(it->path().string().c_str(), it->path().extension().string().c_str(), nstr);
#else
				LoadAsset(it->path().string().c_str(), it->path().extension().string().c_str(), it->path().stem().c_str());
#endif
			}
		}
	}
}

/*! \brief Loads all the assets in the specified asset directory
 */
void AssetManager::LoadAssetsFromAssetDir()
{
	LoadDir(boost::filesystem::path(assetDir).append("/Shaders"));
	LoadDir(assetDir);
	//TODO: Probably make this less awful
	if(shaderPrograms.find("def") == shaderPrograms.end())
	{
		shaderPrograms["def"] = boost::shared_ptr<ShaderProgram>(new ShaderProgram());
		shaderPrograms["def"]->AttachShader(GetShader("VertexShader").get());
		shaderPrograms["def"]->AttachShader(GetShader("FragmentShader").get());
		shaderPrograms["def"]->Link();
	}

	if (shaderPrograms.find("spritesheetp1") == shaderPrograms.end())
	{
		shaderPrograms["spritesheetp1"] = boost::shared_ptr<ShaderProgram>(new ShaderProgram());
		shaderPrograms["spritesheetp1"]->AttachShader(GetShader("SpriteSheetVertexShader").get());
		shaderPrograms["spritesheetp1"]->AttachShader(GetShader("SpriteSheetFragmentShader").get());
		shaderPrograms["spritesheetp1"]->Link();
	}

	if (shaderPrograms.find("spritesheetp2") == shaderPrograms.end())
	{
		shaderPrograms["spritesheetp2"] = boost::shared_ptr<ShaderProgram>(new ShaderProgram());
		shaderPrograms["spritesheetp2"]->AttachShader(GetShader("SpriteSheetVertexShaderP2").get());
		shaderPrograms["spritesheetp2"]->AttachShader(GetShader("SpriteSheetFragmentShaderP2").get());
		shaderPrograms["spritesheetp2"]->Link();
	}

	if (shaderPrograms.find("rawcolor") == shaderPrograms.end())
	{
		shaderPrograms["rawcolor"] = boost::shared_ptr<ShaderProgram>(new ShaderProgram());
		shaderPrograms["rawcolor"]->AttachShader(GetShader("RawColorVertexShader").get());
		shaderPrograms["rawcolor"]->AttachShader(GetShader("RawColorFragmentShader").get());
		shaderPrograms["rawcolor"]->Link();
	}

}

/*! \brief Asset loader destructor
 */
AssetManager::~AssetManager()
{

}