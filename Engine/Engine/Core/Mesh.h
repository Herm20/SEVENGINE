#ifndef MESH_H
#define MESH_H
#include "MeshData.h"
#include <GL/glew.h>

class Mesh 
{
public:
	Mesh();
	~Mesh();
	//boost::shared_ptr<MeshData> data;
	void Render();
};
#endif // !MESH_H
