#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <boost/shared_ptr.hpp>
#include "ShaderProgram.h"
#include "Texture.h"

class Material {
protected:
	boost::shared_ptr<Texture> diffuseTex;
	boost::shared_ptr<Texture> normalTex;
	boost::shared_ptr<Texture> specularTex;
	boost::shared_ptr<ShaderProgram> shaderProgram;
	glm::vec2 uvSize = glm::vec2(1.0f, 1.0f);
	glm::vec2 uvOffset = glm::vec2();

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

	/*! \brief Gets the UV size
	 *
	 * \return (const glm::vec2 &) The uv size
	 */
	inline const glm::vec2 & GetUVSize() { return this->uvSize; }

	/*! \brief Sets the UV size
	 *
	 * \param (glm::vec2) uvSize - The uv size to set
	 */
	inline void SetUVSize(const glm::vec2 &uvSize) { this->uvSize = uvSize; }

	/*! \brief Gets the UV offsets
	 *
	 * \return (const glm::vec2 &) The uv offset
	 */
	inline const glm::vec2 & GetUVOffset() { return this->uvOffset; }

	/*! \brief Sets the UV offsets
	 *
	 * \param (glm::vec2) uvOffsets - The uv offsets to set
	 */
	inline void SetUVOffset(const glm::vec2 &offsets) { this->uvOffset = offsets; }

	const Material & operator=(const Material &m);
	virtual ~Material();
};

#endif // !MESH_H_
