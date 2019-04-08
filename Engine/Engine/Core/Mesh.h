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
	u32 vao;
	u32 vbo;
	u32 ibo;

public:
	Mesh();
	Mesh(boost::shared_ptr<MeshData> meshData);
	Mesh(const Mesh &m);
	const Mesh & operator=(const Mesh &m);
	void Render(glm::vec3 position, boost::shared_ptr<ShaderProgram> shaderProgram, boost::shared_ptr<Texture> texture);
	void Destroy();
	~Mesh();

	inline const u32 GetVertexArrayObject() { return vao; }

	/*! \brief Gets all this meshes submeshes
	 */
	inline const boost::shared_ptr<MeshData> GetSubMeshes() { return subMeshData; }
};

#endif // !MESH_H_
