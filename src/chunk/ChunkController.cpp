#include <chunk/ChunkController.h>
void ChunkController::createChunk(int x, int z)
{
	std::string key = getKey(x, z);
	if (!chunkExists(key)) {
		Chunk* newChunk = new Chunk(glm::vec3(x * CHUNKSIZE_X, 0.0f, z * CHUNKSIZE_Z));
		newChunk->createPseudoRealChunk();
		chunkMap.emplace(key, newChunk);
		cg->createChunkMesh(key, newChunk);
	}
}

void ChunkController::updateChunk(int x, int y, int z)
{
	std::string key = getKey(x, z);
	if (chunkExists(key)) {
		Chunk* newChunk = new Chunk(glm::vec3(x * CHUNKSIZE_X, 0.0f, z * CHUNKSIZE_Z));
		newChunk->createHollowCube();
		delete chunkMap[key];
		chunkMap.erase(key);
		chunkMap.insert(std::make_pair(key, newChunk));
		cg->updateChunkMesh(key, newChunk);
	}
}

bool ChunkController::removeBlock(int x, int y, int z)
{
	glm::ivec3 worldPos = glm::ivec3(x, y, z);
	glm::ivec3 chunkPos = getChunkPosition(worldPos);
	std::string key = getKey(chunkPos.x, chunkPos.z);
	int chunkX = tge::modulus(x, 16);
	int chunkZ = tge::modulus(z, 16);
	int chunkY = abs(y);
	int index = (chunkZ * CHUNKAREA + chunkY * CHUNKSIZE_X + chunkX);
	if (index < 0 || index >= CHUNKVOLUME) {
		return false;
	}
	if (chunkExists(key)) {
		Chunk* chunk = chunkMap[key];
		Block* block = chunk->chunk.at(index);
		if (block->type == BlockType::AIR) {
			return false;
		}
		else {
			block->type = BlockType::AIR;
			cg->updateChunkMesh(key, chunk);
			return true;
		}
	}
	return false;
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
glm::vec3 ChunkController::getChunkPosition(glm::vec3 position)
{
	
	glm::ivec3 chunkPos(position.x / 16, position.y, position.z / 16);
	//To handle negative chunk pos
	if (position.x < 0) {
		chunkPos.x = (position.x + 1) / 16 - 1;
	}
	if (position.y < 0) {
		chunkPos.y += -1;
	}
	if (position.z < 0) {
		chunkPos.z = (position.z + 1) / 16 - 1;
	}
	return chunkPos;
}

void ChunkController::update()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	chunkGenerationInfinite();
	for (auto& kv : cg->chunkMap) {
		kv.second->render();
	}
}

ChunkController::ChunkController(World* world)
{
	this->world = world;
	this->cg = new ChunkGenerator(world, BlockType::STONE);
}
