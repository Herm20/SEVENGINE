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
	u32 ioCount;
	u32 iaCount;
	boost::shared_ptr<Vertex[]> verts = boost::shared_ptr<Vertex[]>(nullptr);
	boost::shared_ptr<u32[]> inds = boost::shared_ptr<u32[]>(nullptr);
	boost::shared_ptr<u32[]> indOffset = boost::shared_ptr<u32[]>(nullptr);
	boost::shared_ptr<u32[]> indAmount = boost::shared_ptr<u32[]>(nullptr);

public:
	MeshData();
	MeshData(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, boost::shared_ptr<u32[]> indOffset, boost::shared_ptr<u32[]> indAmount, u32 vCount, u32 iCount, u32 ioCount, u32 iaCount);
	MeshData(const MeshData &md);
	void CopyVerticesFromVector(const boost::container::vector<Vertex> &verts);
	void CopyIndicesFromVector(const boost::container::vector<u32> &inds);
	void CopyIndOffsetsFromVector(const boost::container::vector<u32> &indOffsets);
	void CopyIndAmountsFromVector(const boost::container::vector<u32> &indAmounts);
	inline u32 GetVertexCount() { return vCount; }
	inline u32 GetIndexCount() { return iCount; }
	inline u32 GetIndOffsetCount() { return ioCount; }
	inline u32 GetIndAmountCount() { return iaCount; }
	inline const Vertex* GetVertices() { return verts.get(); }
	inline const u32* GetIndices() { return inds.get(); }
	inline const u32* GetIndOffsets() { return indOffset.get(); }
	inline const u32* GetIndAmounts() { return indAmount.get(); }
	const MeshData & operator=(const MeshData &md);
	~MeshData();
};

#endif