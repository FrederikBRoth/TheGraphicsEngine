#include "C:\Users\fredd\source\repos\TheGraphicsEngine\TheGraphicsEngine\headers\chunk\ChunkController.h"

void ChunkController::createChunk(int x, int z)
{
	std::string key = getKey(x, z);
	if (!chunkExists(key)) {
		Chunk* newChunk = new Chunk(glm::vec3(x * CHUNKSIZE_X, -16.0f, z * CHUNKSIZE_Z));
		newChunk->createSolidChunk();
		chunkMap.emplace(key, newChunk);
		cg->createChunkMesh(key, newChunk);
	}
}

void ChunkController::updateBlock(int x, int y, int z)
{
	std::string key = getKey(x, z);
	if (chunkExists(key)) {
		Chunk* newChunk = new Chunk(glm::vec3(x * CHUNKSIZE_X, -16.0f, z * CHUNKSIZE_Z));
		newChunk->createHollowCube();
		delete chunkMap[key];
		chunkMap.erase(key);
		chunkMap.insert(std::make_pair(key, newChunk));
		cg->updateChunkMesh(key, newChunk);
	}

}

std::string ChunkController::getKey(int x, int z)
{
	std::string key = "x";
	key += std::to_string(x);
	key += "z";
	key += std::to_string(z);
	return key;
}

bool ChunkController::chunkExists(std::string key)
{
	return chunkMap.count(key);
}

void ChunkController::chunkGenerationInfinite()
{
	const int chunkRenderRadius = 8;
	glm::vec3 chunkPos = world->getChunkWorldPosition();

	int maxX = chunkPos.x + chunkRenderRadius;
	int minX = chunkPos.x - chunkRenderRadius;
	int maxZ = chunkPos.z + chunkRenderRadius;
	int minZ = chunkPos.z - chunkRenderRadius;
	for (int i = minX; i < maxX; i++) {
		for (int j = minZ; j < maxZ; j++) {
			createChunk(i, j);
		}
	}
}

void ChunkController::update()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	chunkGenerationInfinite();
	for (auto& kv : cg->chunkMap) {
		kv.second->render();
	}
	std::cout << getKey(chunkPos.x, chunkPos.z) << std::endl;
}

ChunkController::ChunkController(World* world)
{
	this->world = world;
	this->cg = new ChunkGenerator(world, BlockType::STONE);
}
