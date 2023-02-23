#include <entities/Entity.h>

glm::vec3* Entity::getPosition()
{
	return &position;
}

void Entity::checkCollision(ChunkController* cc)
{
}

void Entity::makeMesh()
{
	mb->loadMesh(ri, MeshConfig(8, true, true, MeshShape::TRIANGLE));
	mb->bind();
}

Entity::Entity(glm::vec3 dimension, glm::vec3 position)
{
	boundingBox = AABB(dimension);
	this->position = position;
	scale = glm::ivec3(1.0f, 1.0f, 1.0f);
	rotation = glm::ivec3(1.0f, 1.0f, 1.0f);
	mb = new MeshBuffer();
}
