#ifndef MESHDATA_H_
#define MESHDATA_H_

#include <memory>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include "Vertex.h"
#include "Types.h"

/*! \class MeshData
 *  \brief Contains mesh data
 */
class MeshData
{
private:
	u32 vCount;
	u32 iCount;
	boost::shared_ptr<Vertex[]> verts = boost::shared_ptr<Vertex[]>(nullptr);
	boost::shared_ptr<u32[]> inds = boost::shared_ptr<u32[]>(nullptr);

public:
	MeshData(u32 vertCount, u32 indCount);
	MeshData(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, u32 vCount, u32 iCount);
	MeshData(const MeshData &md);
	void CopyVerticesFromVector(boost::container::vector<Vertex> verts);
	void CopyIndicesFromVector(boost::container::vector<u32> inds);
	inline u32 getVertexCount() { return vCount; }
	inline u32 getIndexCount() { return iCount; }
	inline const Vertex* getVertices() { return verts.get(); }
	inline const u32* getIndices() { return inds.get(); }
	const MeshData & operator=(const MeshData &md);
	~MeshData();
};

#endif
