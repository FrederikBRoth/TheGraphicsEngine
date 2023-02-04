#ifndef AABB_H
#define AABB_H
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AABB
{
	std::vector<glm::vec3> boundingBox;
	void updateBB(glm::vec3 location);
};

#endif // !AABB_H