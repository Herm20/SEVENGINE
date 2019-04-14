#include <GL/glew.h>
#include <vector>
#include "Mesh.h"

/*! \brief Mesh default constructor
 */
Mesh::Mesh()
{

}

/*! \brief The mesh constructor
 *
 * \param (boost::shared_ptr<MeshData>) meshData - The meshData for the mesh to use
 * \param (boost::shared_ptr<ShaderProgram>) sp - The shader program for this mesh to use
 * \param (boost::shared_ptr<Texture>) t - The texture for the mesh to use
 * \param (glm::vec3) position - The position of the mesh
 */
Mesh::Mesh(boost::shared_ptr<MeshData> meshData) :
	subMeshData(boost::shared_ptr<MeshData>(meshData))
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * subMeshData->GetVertexCount(), subMeshData->GetVertices(), GL_STATIC_DRAW);

	// Describe buffer layout

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					// Attribute index
		3,					// Number of components (x, y, z)
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		0					// Offset to this attribute
	);

	// UVs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,					// Attribute index
		2,					// Number of components
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(void*)sizeof(glm::vec3)	// Offset to this attribute
	);

	// Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,					// Attribute index
		3,					// Number of components
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2))	// Offset to this attribute
	);

	// TODO: Add in tangents and bitangents

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * subMeshData->GetIndexCount(), subMeshData->GetIndices(), GL_STATIC_DRAW);
}

/*! \brief Mesh copy constructor
 *
 * \param (const Mesh &) m - The mesh to copy
 */
Mesh::Mesh(const Mesh &m)
{
	this->subMeshData = boost::shared_ptr<MeshData>(m.subMeshData);
	this->vao = m.vao;
	this->vbo = m.vbo;
	this->ibo = m.ibo;
}

/*! \brief Mesh copy-assignment operator
 *
 * \param (const Mesh &) m - The mesh to copy
 *
 * \return This mesh after assignment
 */
const Mesh & Mesh::operator=(const Mesh &m)
{
	this->subMeshData = boost::shared_ptr<MeshData>(m.subMeshData);
	this->vao = m.vao;
	this->vbo = m.vbo;
	this->ibo = m.ibo;

	return *this;
}

void Mesh::Render(glm::vec3 position, boost::shared_ptr<ShaderProgram> shaderProgram, boost::shared_ptr<Texture> texture, bool wireframe) {
	glm::mat4 posMatrix = glm::translate(glm::mat4(1.0), position);
	shaderProgram->Use();
	glBindVertexArray(this->vao);
	// TODO: Move this out of here
	glUniformMatrix4fv(3, 1, GL_FALSE, &posMatrix[0][0]);
	texture->bind(0);
	glUniform1i(glGetUniformLocation(shaderProgram->GetProgram(), "tex"), 0);
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	for (u32 i = 0; i < this->subMeshData->GetIndAmountCount(); i++) {
		glDrawElements(
			GL_TRIANGLES, 
			this->subMeshData->GetIndAmounts()[i], 
			GL_UNSIGNED_INT, 
			(const void*)(this->subMeshData->GetIndOffsets()[i] * sizeof(u32)));
	}
	texture->unbind(0);
}

/*! \brief Cleans up a mesh
 */
void Mesh::Destroy()
{
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

/*! \brief Mesh destructor
 */
Mesh::~Mesh()
{

}