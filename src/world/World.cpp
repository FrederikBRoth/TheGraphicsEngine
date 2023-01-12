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

void World::generateChunk()
{
	if ((worldX % 16 == 0 || worldZ % 16 == 0) && hasFinishedRendering) {
		Chunk* newChunk = new Chunk(glm::vec3(worldX, -16.0f, worldZ));
		newChunk->createSolidChunk();
		TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
		ChunkBuilder cb = ChunkBuilder(tm->getTexCoords(0, 2));
		chunks.push_back(new IndexedMesh((cb.getChunkMesh(newChunk))));
		hasFinishedRendering = false;
	}
	else {
		hasFinishedRendering = true;
	}
}

void World::update()
{
	generateChunk();
	for (auto chunk : chunks) {
		chunk->render();
	}
}

World::World()
{
	worldX = 0;
	worldY = 0;
	worldZ = 0;
	hasFinishedRendering = false;

}
