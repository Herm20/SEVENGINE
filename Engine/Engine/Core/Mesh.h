#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/lexical_cast.hpp>
#include "Transform.h"
#include "Systems/Camera.h"
#include "MeshData.h"
#include "Material.h"
#include "Light.h"
#include "SpriteSheet.h"

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
	void Render(const Transform &trans, const CameraSystem* cam, boost::shared_ptr<Material> material, const boost::container::vector<Light> &lights, bool wireframe = false);
	void Destroy();
	~Mesh();

	inline const u32 GetVertexArrayObject() { return vao; }

	/*! \brief Gets all this meshes submeshes
	 */
	inline const boost::shared_ptr<MeshData> GetSubMeshes() { return subMeshData; }
};

#endif // !MESH_H_
