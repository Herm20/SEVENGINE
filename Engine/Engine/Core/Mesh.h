#ifndef MESH_H_
#define MESH_H_

#include <memory>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include "Vertex.h"
#include "Types.h"

/*! \class MeshData
 *  \brief Contains mesh data
 */
class Mesh
{
private:
	u32 vCount;
	u32 iCount;
	boost::shared_ptr<Vertex[]> verts = boost::shared_ptr<Vertex[]>(nullptr);
	boost::shared_ptr<u32[]> inds = boost::shared_ptr<u32[]>(nullptr);

public:
	Mesh();
	Mesh(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, u32 vCount, u32 iCount);
	Mesh(const Mesh &md);
	void CopyVerticesFromVector(const boost::container::vector<Vertex> &verts);
	void CopyIndicesFromVector(const boost::container::vector<u32> &inds);
	inline u32 getVertexCount() { return vCount; }
	inline u32 getIndexCount() { return iCount; }
	inline const Vertex* getVertices() { return verts.get(); }
	inline const u32* getIndices() { return inds.get(); }
	const Mesh & operator=(const Mesh &md);
	~Mesh();
};

#endif
