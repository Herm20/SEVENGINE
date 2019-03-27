#include "Mesh.h"

/*! \brief Mesh constructor
 */
Mesh::Mesh()
{

}

/*! \brief Mesh constructor
 *
 * \param (boost::shared_ptr<Vertex[]>) verts - The vertex data of the mesh
 * \param (boost::shared_ptr<u32[]>) inds - The index data of the mesh
 * \param (u32) vertexCount - The vertex count
 * \param (u32) indexCount - The index count
 */
Mesh::Mesh(boost::shared_ptr<Vertex[]> verts, boost::shared_ptr<u32[]> inds, u32 vCount, u32 iCount) :
	vCount(vCount),
	iCount(iCount),
	verts(verts),
	inds(inds)
{

}

/*! \brief Mesh copy constructor
 *
 * \param (const Mesh &) md - The mesh data to copy
 */
Mesh::Mesh(const Mesh &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->vCount = md.vCount;
	this->iCount = md.iCount;
}

/*! \brief Copies vertex information from a vertex array
 *
 * \param (const boost::container::vector<Vertex> &) verts - The vertex array to copy
 */
void Mesh::CopyVerticesFromVector(const boost::container::vector<Vertex> &verts)
{
	vCount = verts.size();
	this->verts = boost::shared_ptr<Vertex[]>(new Vertex[vCount]);
	std::copy(verts.begin(), verts.end(), this->verts.get());
}

/*! \brief Copies index information from an index array
 *
 * \param (const boost::container::vector<u32> &) inds - The index array to copy
 */
void Mesh::CopyIndicesFromVector(const boost::container::vector<u32> &inds)
{
	iCount = inds.size();
	this->inds = boost::shared_ptr<u32[]>(new u32[iCount]);
	std::copy(inds.begin(), inds.end(), this->inds.get());
}

/*! \brief Mesh copy constructor
 *
 * \param (const Mesh &) md - The mesh data to copy
 *
 * \return (const Mesh &) This mesh data after copying
 */
const Mesh & Mesh::operator=(const Mesh &md)
{
	this->verts = boost::shared_ptr<Vertex[]>(md.verts);
	this->inds = boost::shared_ptr<u32[]>(md.inds);
	this->vCount = md.vCount;
	this->iCount = md.iCount;

	return *this;
}

/*! \brief Mesh data destructor
 */
Mesh::~Mesh()
{

}
