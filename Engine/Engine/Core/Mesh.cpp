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
		(const void*)offsetof(Vertex, uv)	// Offset to this attribute
	);

	// Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,					// Attribute index
		3,					// Number of components
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(const void*)offsetof(Vertex, norm)	// Offset to this attribute
	);

	// Tans
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,					// Attribute index
		3,					// Number of components
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(const void*)offsetof(Vertex, tan)	// Offset to this attribute
	);

	// Bitans
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,					// Attribute index
		3,					// Number of components
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(const void*)offsetof(Vertex, bitan)	// Offset to this attribute
	);

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

void Mesh::Render(const Transform &trans, const CameraSystem* cam, boost::shared_ptr<Material> material, const boost::container::vector<Light> &lights, bool wireframe) {
	material->GetShaderProgram()->Use();
	glBindVertexArray(this->vao);
	glUniformMatrix4fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "model"), 1, GL_FALSE, &trans.GetMatrix()[0][0]);
	glUniformMatrix3fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "invTrans"), 1, GL_FALSE, &trans.GetInverseTransposeMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "cameraMatrix"), 1, GL_FALSE, &cam->cameraMatrix[0][0]);
	glUniform3fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "camPos"), 1, &cam->position[0]);
	material->GetDiffuseTexture()->bind(0);
	glUniform1i(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "diffuse"), 0);

	if (material->GetNormalTexture() != nullptr) {
		material->GetNormalTexture()->bind(1);
		glUniform1i(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "normal"), 1);
	}

	if (material->GetSpecularTexture() != nullptr) {
		material->GetSpecularTexture()->bind(2);
		glUniform1i(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "specular"), 2);
	}

	glUniform2fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "scaleSize"), 1, &material->GetUVSize()[0]);
	glUniform2fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "offset"), 1, &material->GetUVOffset()[0]);

	boost::container::string str;
	for (u32 i = 0; i < lights.size(); i++)
	{
		str = "lights[";
		str += boost::lexical_cast<boost::container::string>(i);
		str += "]";
		glUniform3fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), boost::container::string(str + ".pos").c_str()), 1, &lights[i].pos[0]);
		glUniform1f(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), boost::container::string(str + ".radius").c_str()), lights[i].radius);
		glUniform3fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), boost::container::string(str + ".color").c_str()), 1, &lights[i].color[0]);
		glUniform1f(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), boost::container::string(str + ".intensity").c_str()), lights[i].intensity);
		glUniform3fv(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), boost::container::string(str + ".dir").c_str()), 1, &lights[i].dir[0]);
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	for (u32 i = 0; i < this->subMeshData->GetIndAmountCount(); i++) {
		glDrawElements(
			GL_TRIANGLES,
			this->subMeshData->GetIndAmounts()[i],
			GL_UNSIGNED_INT,
			(const void*)(this->subMeshData->GetIndOffsets()[i] * sizeof(u32)));
	}

	material->GetDiffuseTexture()->unbind(0);

	if (material->GetNormalTexture() != nullptr)
		material->GetNormalTexture()->unbind(1);

	if (material->GetSpecularTexture() != nullptr)
		material->GetSpecularTexture()->unbind(2);
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