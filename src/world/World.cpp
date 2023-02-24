#include <world/World.h>
#include <entities/Entity.h>

void World::updateWorldPosition(glm::vec3& position)
{
	/*worldX = floor((position.x*2.0f));
	worldY = floor((position.y*2.0f));
	worldZ = floor((position.z*2.0f));*/
	worldPos = tge::getBlockPosition(position);
}

glm::vec3 World::getWorldPosition()
{
	return worldPos;
}

glm::vec3 World::getChunkWorldPosition()
{
	return tge::getChunkPosition(glm::ivec3(worldPos.x, worldPos.y, worldPos.z));
}

void World::update()
{
	/*generateChunk();
	for (auto chunk : chunks) {
		chunk->render();
	}*/
}

World::World()
{
	worldPos = glm::ivec3(0, 0, 0);

}
