#ifndef MESH_H
#define MESH_H
#include "MeshData.h"
#include <GL/glew.h>

class Mesh 
{
public:
	Mesh();
	~Mesh();
	bool Load(MeshData* _data);
	void Render(MeshData* _data);
};
#endif // !MESH_H
