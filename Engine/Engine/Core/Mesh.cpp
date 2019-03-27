#include "Mesh.h"

#include <GL/glew.h>
#include <vector>

Mesh::Mesh(boost::shared_ptr<MeshData> meshData) {

	vertCount = meshData->getVertexCount();
	const Vertex* vertBufData = meshData->getVertices();

	GLuint vertBuf;
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// Store data in buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(Vertex) * this->vertCount,
		&vertBufData[0],
		GL_STATIC_DRAW
	);

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

}

void Mesh::Render() {
	glBindVertexArray(this->vertArr);
	glDrawArrays(GL_TRIANGLES, 0, this->vertCount);
}