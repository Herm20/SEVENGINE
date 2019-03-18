#ifndef MESHDATA_H_
#define MESHDATA_H_

#include <memory>
#include <boost/container/vector.hpp>
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
	std::shared_ptr<Vertex[]> verts = std::shared_ptr<Vertex[]>(nullptr);
	std::shared_ptr<u32[]> inds = std::shared_ptr<u32[]>(nullptr);

public:
	MeshData(u32 vertCount, u32 indCount);
	MeshData(std::shared_ptr<Vertex[]> verts, std::shared_ptr<u32[]> inds, u32 vCount, u32 iCount);
	MeshData(const MeshData &md);
	void CopyVerticesFromVector(boost::container::vector<Vertex> verts);
	void CopyIndicesFromVector(boost::container::vector<u32> inds);
	const MeshData & operator=(const MeshData &md);
	~MeshData();
};

#endif
