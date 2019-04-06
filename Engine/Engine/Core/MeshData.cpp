#include "MeshData.h"

/*! \brief Mesh constructor
 */
MeshData::MeshData()
{

}

/*! \brief Mesh constructor
 *
 * \param (boost::shared_ptr<Vertex[]>) verts - The vertex data of the mesh
 * \param (boost::shared_ptr<u32[]>) inds - The index data of the mesh
 * \param (boost::shared_ptr<u32[]>) indOffset - The offsets of the index data of the mesh
 * \param (boost::shared_ptr<u32[]>) indAmount - The amount to skip for the index data of the mesh
 * \param (u32) vCount - The vertex count
 * \param (u32) iCount - The index count
 * \param (u32) ioCount - The index offset count
 * \param (u32) iaCount - The index amount count
 */
MeshData::MeshData(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, boost::shared_ptr<u32[]> indOffset, boost::shared_ptr<u32[]> indAmount, u32 vCount, u32 iCount, u32 ioCount, u32 iaCount) :
	vCount(vCount),
	iCount(iCount),
	ioCount(ioCount),
	iaCount(iaCount),
	verts(verts),
	inds(inds),
	indOffset(indOffset),
	indAmount(indAmount)
{

}

/*! \brief Mesh copy constructor
 *
 * \param (const Mesh &) md - The mesh data to copy
 */
MeshData::MeshData(const MeshData &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->indOffset = boost::shared_ptr<u32[]>(md.indOffset);
	this->indAmount = boost::shared_ptr<u32[]>(md.indAmount);
	this->vCount = md.vCount;
	this->iCount = md.iCount;
	this->ioCount = md.ioCount;
	this->iaCount = md.iaCount;
}

/*! \brief Copies vertex information from a vertex array
 *
 * \param (const boost::container::vector<Vertex> &) verts - The vertex array to copy
 */
void MeshData::CopyVerticesFromVector(const boost::container::vector<Vertex> &verts)
{
	vCount = verts.size();
	this->verts = boost::shared_ptr<Vertex[]>(new Vertex[vCount]);
	std::copy(verts.begin(), verts.end(), this->verts.get());
}

/*! \brief Copies index information from an index array
 *
 * \param (const boost::container::vector<u32> &) inds - The index array to copy
 */
void MeshData::CopyIndicesFromVector(const boost::container::vector<u32> &inds)
{
	iCount = inds.size();
	this->inds = boost::shared_ptr<u32[]>(new u32[iCount]);
	std::copy(inds.begin(), inds.end(), this->inds.get());
}

/*! \brief Copies index offset information from an offset array
 *
 * \param (const boost::container::vector<u32> &) indOffsets - The offset array to copy
 */
void MeshData::CopyIndOffsetsFromVector(const boost::container::vector<u32> &indOffsets)
{
	ioCount = indOffsets.size();
	this->indOffset = boost::shared_ptr<u32[]>(new u32[ioCount]);
	std::copy(indOffsets.begin(), indOffsets.end(), this->indOffset.get());
}

/*! \brief Copies index amount information from an index amount array
 *
 * \param (const boost::container::vector<u32> &) indAmount- The index amount array to copy
 */
void MeshData::CopyIndAmountsFromVector(const boost::container::vector<u32> &indAmounts)
{
	iaCount = indAmounts.size();
	this->indAmount = boost::shared_ptr<u32[]>(new u32[iaCount]);
	std::copy(indAmounts.begin(), indAmounts.end(), this->indAmount.get());
}

/*! \brief Mesh copy constructor
 *
 * \param (const Mesh &) md - The mesh data to copy
 *
 * \return (const Mesh &) This mesh data after copying
 */
const MeshData & MeshData::operator=(const MeshData &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->indOffset = boost::shared_ptr<u32[]>(md.indOffset);
	this->indAmount = boost::shared_ptr<u32[]>(md.indAmount);
	this->vCount = md.vCount;
	this->iCount = md.iCount;
	this->ioCount = md.ioCount;
	this->iaCount = md.iaCount;

	return *this;
}

/*! \brief Mesh data destructor
 */
MeshData::~MeshData()
{

}
