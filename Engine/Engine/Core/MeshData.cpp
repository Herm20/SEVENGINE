#include "MeshData.h"

/*! \brief MeshData constructor
 *
 * \param (u32) vertexCount - The vertex count
 * \param (u32) indexCount - The index count
 */
MeshData::MeshData(u32 vertCount, u32 indCount) :
	verts(boost::shared_ptr<Vertex[]>(new Vertex[vertCount])),
	inds(boost::shared_ptr<u32[]>(new u32[indCount])),
	vCount(vertCount),
	iCount(indCount)
{

}

/*! \brief MeshData constructor
 *
 * \param (boost::shared_ptr<Vertex[]>) verts - The vertex data of the mesh
 * \param (boost::shared_ptr<u32[]>) inds - The index data of the mesh
 * \param (u32) vertexCount - The vertex count
 * \param (u32) indexCount - The index count
 */
MeshData::MeshData(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, u32 vCount, u32 iCount) :
	verts(verts),
	inds(inds),
	vCount(vCount),
	iCount(iCount)
{

}

/*! \brief MeshData copy constructor
 *
 * \param (const MeshData &) md - The mesh data to copy
 */
MeshData::MeshData(const MeshData &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->vCount = md.vCount;
	this->iCount = md.iCount;
}

/*! \brief Copies vertex information from a vertex array
 *
 * \param (boost::container::vector<Vertex>) verts - The vertex array to copy
 */
void MeshData::CopyVerticesFromVector(boost::container::vector<Vertex> verts)
{
	std::copy(verts.begin(), verts.end(), this->verts.get());
}

/*! \brief Copies index information from an index array
 *
 * \param (boost::container::vector<u32>) inds - The index array to copy
 */
void MeshData::CopyIndicesFromVector(boost::container::vector<u32> inds)
{
	std::copy(inds.begin(), inds.end(), this->inds.get());
}

/*! \brief MeshData copy constructor
 *
 * \param (const MeshData &) md - The mesh data to copy
 *
 * \return (const MeshData &) This mesh data after copying
 */
const MeshData & MeshData::operator=(const MeshData &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->vCount = md.vCount;
	this->iCount = md.iCount;

	return *this;
}

/*! \brief Mesh data destructor
 */
MeshData::~MeshData()
{

}
