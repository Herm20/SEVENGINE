#ifndef MESH_H_
#define MESH_H_

#include "MeshData.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh {

private:

	unsigned int vertCount;
	GLuint vertArr;

public:

	Mesh(boost::shared_ptr<MeshData> meshData);

	void Render();

};

#endif // !MESH_H_
