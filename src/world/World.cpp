#include <world/World.h>


void World::updateWorldPosition(glm::vec3& position)
{
	worldX = (int)floorf(position.x*2.0f);
	worldY = (int)floorf(position.y*2.0f);
	worldZ = (int)floorf(position.z*2.0f);
}

glm::vec3 World::getWorldPosition()
{
	return glm::vec3();
}

glm::vec3 World::getChunkWorldPosition()
{
	return glm::vec3(worldX/16, worldY, worldZ / 16);
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
	hasFinishedRendering = false;

}
