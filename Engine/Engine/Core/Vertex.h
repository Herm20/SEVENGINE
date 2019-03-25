#ifndef VERTEX_H_
#define VERTEX_H_

#include "glm/glm.hpp"

/*! \struct Vertex
 *  \brief Helper structure for holding mesh data
 */
struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
	glm::vec3 tan;
	glm::vec3 bitan;
};

#endif
