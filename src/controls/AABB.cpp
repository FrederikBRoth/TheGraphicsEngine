#include <controls/AABB.h>

void AABB::updateBB(glm::vec3 location)
{
	boundingBox = location;
}

AABB::AABB(glm::vec3 dimension)
{
	this->dimension = dimension;
	this->boundingBox = { 0, 0, 0 };
}
