#include <world/World.h>


void World::updateWorldPosition(glm::vec3& position)
{
	worldX = floor((position.x*2.0f));
	worldY = floor((position.y*2.0f));
	worldZ = floor((position.z*2.0f));
}

glm::vec3 World::getWorldPosition()
{
	return glm::vec3();
}

glm::vec3 World::getChunkWorldPosition()
{
	glm::vec3 chunkPos(worldX / 16, worldY, worldZ / 16);
	//To handle negative chunk pos
	if (worldX < 0) {
		chunkPos.x += -1;
	}
	if (worldY < 0) {
		chunkPos.y += -1;
	}
	if (worldZ < 0) {
		chunkPos.z += -1;
	}
	return chunkPos;
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
	worldX = 0;
	worldY = 0;
	worldZ = 0;


}
