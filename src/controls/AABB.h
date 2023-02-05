#ifndef AABB_H
#define AABB_H
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AABB
{
public:
	glm::vec3 dimension;
	glm::vec3 boundingBox;
	void updateBB(glm::vec3 location);
	AABB(glm::vec3 dimension);
};

#endif // !AABB_H