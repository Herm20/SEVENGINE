#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <boost/shared_ptr.hpp>
#include "ShaderProgram.h"
#include "Texture.h"

class Material {
private:
	boost::shared_ptr<Texture> diffuseTex;
	boost::shared_ptr<Texture> normalTex;
	boost::shared_ptr<Texture> specularTex;
	boost::shared_ptr<ShaderProgram> shaderProgram;

public:
	Material();
	Material(boost::shared_ptr<Texture> diffuseTex, boost::shared_ptr<Texture> normalTex, boost::shared_ptr<Texture> specularTex, boost::shared_ptr<ShaderProgram> program);
	Material(const Material &m);

	/*! \brief Gets the diffuse texture
	 *
	 * \return (boost::shared_ptr<Texture>) The diffuse texture
	 */
	inline boost::shared_ptr<Texture> GetDiffuseTexture() { return this->diffuseTex; }

	/*! \brief Sets the materials diffuse texture
	 *
	 * \param (boost::shared_ptr<Texture>) diffuseTex - The diffuse tex
	 */
	inline void SetDiffuseTexture(boost::shared_ptr<Texture> diffuseTex) { this->diffuseTex = boost::shared_ptr<Texture>(diffuseTex); }

	/*! \brief Gets the normal texture
	 *
	 * \return (boost::shared_ptr<Texture>) The normal texture
	 */
	inline boost::shared_ptr<Texture> GetNormalTexture() { return this->normalTex; }

	/*! \brief Sets the materials normal texture
	 *
	 * \param (boost::shared_ptr<Texture>) normalTex - The normal tex
	 */
	inline void SetNormalTexture(boost::shared_ptr<Texture> normalTex) { this->normalTex = boost::shared_ptr<Texture>(normalTex); }

	/*! \brief Gets the specular texture
	 *
	 * \return (boost::shared_ptr<Texture>) The specular texture
	 */
	inline boost::shared_ptr<Texture> GetSpecularTexture() { return this->specularTex; }

	/*! \brief Sets the materials specular texture
	*
	* \param (boost::shared_ptr<Texture>) specularTex - The specular tex
	*/
	inline void SetSpecularTexture(boost::shared_ptr<Texture> specularTex) { this->specularTex = boost::shared_ptr<Texture>(specularTex); }

	/*! \brief Gets the shader program
	 *
	 * \return (boost::shared_ptr<ShaderProgram>) The shaderProgram
	 */
	inline boost::shared_ptr<ShaderProgram> GetShaderProgram() { return this->shaderProgram; }

	/*! \brief Sets the materials shader program
	 *
	 * \param (boost::shared_ptr<ShaderProgram>) program - The shader program to use
	 */
	inline void SetShaderProgram(boost::shared_ptr<ShaderProgram> program) { this->shaderProgram = program; }

	const Material & operator=(const Material &m);
	~Material();
};

#endif // !MESH_H_
