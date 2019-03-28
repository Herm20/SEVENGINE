#include "Mesh.h"

#include <GL/glew.h>
#include <vector>

Mesh::Mesh(boost::shared_ptr<MeshData> meshData) {

	vertCount = meshData->getVertexCount();
	const Vertex* vertBufData = meshData->getVertices();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Store data in buffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(Vertex) * vertCount,
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

	// Index buffer
	indexCount = meshData->getIndexCount();
	const u32* indBufData = meshData->getIndices();

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(u32) * indexCount,
		&indBufData[0],
		GL_STATIC_DRAW
	);

}

void Mesh::Render() {
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, this->vertCount);
}