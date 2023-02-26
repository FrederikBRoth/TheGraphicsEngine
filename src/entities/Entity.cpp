#include <entities/Entity.h>

glm::vec3* Entity::getPosition()
{
	return &position;
}

float Entity::getScale()
{
	return scale;
}

float Entity::getRotation()
{
	return yaw;
}

void Entity::checkCollision(ChunkController* cc)
{
}

void Entity::makeMesh()
{
	mb->loadMesh(ri, MeshConfig(8, true, true, MeshShape::TRIANGLE));
	mb->bind();
}

Entity::Entity(glm::vec3 dimension, glm::vec3 position, float yaw, float scale)
{
	boundingBox = AABB(dimension);
	this->position = position;
	this->scale = scale;
	this->yaw = yaw;
	mb = new MeshBuffer();
}
