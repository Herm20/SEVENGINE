#include "Material.h"

/*! \brief Mesh default constructor
 */
Material::Material() :
	diffuseTex(boost::shared_ptr<Texture>(nullptr)),
	normalTex(boost::shared_ptr<Texture>(nullptr)),
	specularTex(boost::shared_ptr<Texture>(nullptr)),
	shaderProgram(boost::shared_ptr<ShaderProgram>(nullptr))
{

}

/*! \brief Creates a material using parameters
 *
 * \param (boost::shared_ptr<Texture>) diffuseTex - The diffuse tex
 * \param (boost::shared_ptr<Texture>) normalTex - The normal tex
 * \param (boost::shared_ptr<Texture>) specularTex - The specular tex
 * \param (boost::shared_ptr<ShaderProgram>) program - The shader program
 */
Material::Material(boost::shared_ptr<Texture> diffuseTex, boost::shared_ptr<Texture> normalTex, boost::shared_ptr<Texture> specularTex, boost::shared_ptr<ShaderProgram> program) :
	diffuseTex(boost::shared_ptr<Texture>(diffuseTex)),
	normalTex(boost::shared_ptr<Texture>(normalTex)),
	specularTex(boost::shared_ptr<Texture>(specularTex)),
	shaderProgram(boost::shared_ptr<ShaderProgram>(program))
{

}

/*! \brief Material copy constructor
 *
 * \param (const Material &) m - The mesh to copy
 */
Material::Material(const Material &m)
{
	this->diffuseTex = boost::shared_ptr<Texture>(m.diffuseTex);
	this->normalTex = boost::shared_ptr<Texture>(m.normalTex);
	this->specularTex = boost::shared_ptr<Texture>(m.specularTex);
	this->shaderProgram = boost::shared_ptr<ShaderProgram>(m.shaderProgram);
}

/*! \brief Material copy assignment operator
 *
 * \param (const Material &) m - The mesh to copy
 *
 * \return (const Material &) This material after copying
 */
const Material & Material::operator=(const Material &m)
{
	this->diffuseTex = boost::shared_ptr<Texture>(m.diffuseTex);
	this->normalTex = boost::shared_ptr<Texture>(m.normalTex);
	this->specularTex = boost::shared_ptr<Texture>(m.specularTex);
	this->shaderProgram = boost::shared_ptr<ShaderProgram>(m.shaderProgram);

	return *this;
}

Material::~Material()
{

}