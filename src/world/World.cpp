#include <world/World.h>

void World::updateWorldPosition(float x, float y, float z)
{
	worldX = (int)floorf(x);
	worldY = (int)floorf(y);
	worldZ = (int)floorf(z);
}

glm::u32vec3 World::getWorldPosition()
{
	return glm::u32vec3();
}

void World::generateChunk()
{
}

void World::update()
{
}
