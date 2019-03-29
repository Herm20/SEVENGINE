#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
	glm::vec3 tan;
	glm::vec3 bitan;
};

#endif // !VERTEX_H_
