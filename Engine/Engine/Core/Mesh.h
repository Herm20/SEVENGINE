#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MeshData.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Mesh {

private:
	boost::shared_ptr<MeshData> subMeshData;
	boost::shared_ptr<ShaderProgram> shaderProgram;
	boost::shared_ptr<Texture> tex;
	u32 vao;
	u32 vbo;
	u32 ibo;

public:
	Mesh();
	Mesh(boost::shared_ptr<MeshData> meshData, boost::shared_ptr<ShaderProgram> sp, boost::shared_ptr<Texture> t, glm::vec3 position);
	Mesh(const Mesh &m);
	void SetMeshData(boost::shared_ptr<MeshData> meshData);
	void Render();
	const Mesh & operator=(const Mesh &m);
	void Destroy();
	~Mesh();

	//TODO: Remove temp position
	glm::vec3 position;

	/*! \brief Gets all this meshes submeshes
	 */
	inline const boost::shared_ptr<MeshData> GetSubMeshes() { return subMeshData; }

	/*! \brief Gets the meshes shader GetShaderProgram
	 *
	 * \return (const ShaderProgram*) The shader program of this mesh
	 */
	inline const ShaderProgram* GetShaderProgram() { return shaderProgram.get(); }
};

#endif // !MESH_H_
