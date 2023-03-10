#include <chunk/ChunkController.h>
#include <helpers/RenderDistance.h>

void ChunkController::createChunk(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);
	if (!chunkExists(key)) {
		glm::vec3 position = glm::vec3(x * CHUNKSIZE_X, 0.0f, z * CHUNKSIZE_Z);
		Chunk* newChunk = new Chunk(position);
		chunkMap.insert(std::make_pair(key, newChunk));
	}
}

void ChunkController::createChunkBlocks(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);
	if (chunkExists(key) && chunkMap[key]->genFinished == false) {
		chunkMap[key]->createPerlinNoiseChunk(pn.generateNoiseMap(chunkMap[key]->position, 20, 0.025), tg);
	}
}

void ChunkController::createChunkMesh(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);
	if (chunkExists(key)) {
		mb->createChunkMesh(key, &chunkMap);
	}
}

void ChunkController::updateChunk(int x, int y, int z)
{
	VectorXZ key = tge::getKey(x, z);
	if (chunkExists(key)) {
		Chunk* newChunk = new Chunk(glm::vec3(x * CHUNKSIZE_X, 0.0f, z * CHUNKSIZE_Z));
		newChunk->createHollowCube();
		delete chunkMap[key];
		chunkMap.erase(key);
		chunkMap.insert(std::make_pair(key, newChunk));
		//std::unique_lock<std::mutex> lock(generationMutex);
		mb->updateChunkMesh(key, &chunkMap);
	}
}

void ChunkController::removeChunk(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);

	if (chunkExists(key)) {
		delete chunkMap[key];
		chunkMap.erase(key);
		//std::unique_lock<std::mutex> lock(generationMutex);
		mb->removeChunkMesh(key);
	}
}

BlockType ChunkController::removeBlock(int x, int y, int z)
{
	Block* block = getBlock(x, y, z);
	if (block != nullptr) {
		BlockType before = block->type;
		block->type = BlockType::AIR;
		block->isCollidable = false;
		//std::unique_lock<std::mutex> lock(generationMutex);
		glm::ivec3 worldPos = glm::ivec3(x, y, z);
		glm::ivec3 chunkPos = getChunkPosition(worldPos);
		VectorXZ key = tge::getKey(chunkPos.x, chunkPos.z);
		int chunkX = tge::modulus(x, 16);
		int chunkZ = tge::modulus(z, 16);
		int chunkY = abs(y);
		int index = (chunkZ * CHUNKAREA + chunkY * CHUNKSIZE_X + chunkX);
		mb->updateChunkMesh(key, &chunkMap);
		updateChunkEdges(chunkX, chunkZ, key);
		return before;	
	}
	return BlockType::NOTHING;
}

Block* ChunkController::getBlock(int x, int y, int z)
{
	glm::ivec3 worldPos = glm::ivec3(x, y, z);
	glm::ivec3 chunkPos = getChunkPosition(worldPos);
	VectorXZ key = tge::getKey(chunkPos.x, chunkPos.z);
	int chunkX = tge::modulus(x, 16);
	int chunkZ = tge::modulus(z, 16);
	int chunkY = abs(y);
	int index = (chunkZ * CHUNKAREA + chunkY * CHUNKSIZE_X + chunkX);
	if (index < 0 || index >= CHUNKVOLUME) {
		return nullptr;
	}
	if (chunkExists(key)) {
		Chunk* chunk = chunkMap[key];
		Block* block = chunk->chunk.at(index);
		if (block->type == BlockType::AIR) {
			return nullptr;
		}
		else {
			return chunk->chunk.at(index);
		}
	}
	return nullptr;
}

Block* ChunkController::getBlock(int index, VectorXZ key)
{
	if(index < 0 || index >= CHUNKVOLUME) {
		return nullptr;
	}
	if (chunkExists(key)) {
		Chunk* chunk = chunkMap[key];
		Block* block = chunk->chunk.at(index);
		return chunk->chunk.at(index);
		
	}
	return nullptr;
}

void ChunkController::updateBlock(int x, int y, int z, glm::vec3 relative, BlockType type)
{
	Block* block = getBlock(x, y, z);
	if (block != nullptr) {
		//std::unique_lock<std::mutex> lock(generationMutex);
		glm::ivec3 worldPos = glm::ivec3(x, y, z);
		glm::ivec3 chunkPos = getChunkPosition(worldPos);
		VectorXZ key = tge::getKey(chunkPos.x, chunkPos.z);
		int chunkX = tge::modulus(x, 16);
		int chunkZ = tge::modulus(z, 16);
		int chunkY = abs(y);
		glm::vec3 newBlockPos = glm::vec3(chunkX, chunkY, chunkZ) + relative;
		if (newBlockPos.x > 15) {
			key = { key.x + 1, key.z };
			newBlockPos.x = 0;
		}
		if (newBlockPos.x < 0) {
			key = { key.x - 1, key.z };
			newBlockPos.x = 15;
		}
		if (newBlockPos.z > 15) {
			key = { key.x, key.z + 1 };
			newBlockPos.z = 0;
		}
		if (newBlockPos.z < 0) {
			key = { key.x, key.z - 1 };
			newBlockPos.z = 15;
		}
		int newindex = (newBlockPos.z * CHUNKAREA + newBlockPos.y * CHUNKSIZE_X + newBlockPos.x);
		Block* newBlock = getBlock(newindex, key);
		if (newBlock != nullptr) {
			if (newBlock->type == BlockType::AIR) {
				newBlock->type = type;
				newBlock->isCollidable = true;
				mb->updateChunkMesh(key, &chunkMap);
				updateChunkEdges(chunkX, chunkZ, key);
			}

		}

	}
}

void ChunkController::updateChunkEdges(int x, int z, VectorXZ key)
{
	VectorXZ newKey;
	if (x == 15) {
		newKey = { key.x + 1, key.z };
		mb->updateChunkMesh(newKey, &chunkMap);
	}
	if (x == 0) {
		newKey = { key.x - 1, key.z };
		mb->updateChunkMesh(newKey, &chunkMap);
	}
	if (z == 15) {
		newKey = { key.x, key.z + 1 };
		mb->updateChunkMesh(newKey, &chunkMap);
	}
	if (z == 0) {
		newKey = { key.x, key.z - 1 };
		mb->updateChunkMesh(newKey, &chunkMap);
	}
}


bool ChunkController::chunkExists(VectorXZ key)
{
	return chunkMap.count(key);
}

void ChunkController::chunkMeshGeneration()
{
	while (isRunning) {
		glm::vec3 chunkPos = world->getChunkWorldPosition();
		int maxX = chunkPos.x + RENDER_DISTANCE;
		int minX = chunkPos.x - RENDER_DISTANCE;
		int maxZ = chunkPos.z + RENDER_DISTANCE;
		int minZ = chunkPos.z - RENDER_DISTANCE;
		std::unique_lock<std::mutex> lock(generationMutex);
		for (int i = minX-2; i < maxX+2; i++) {
			for (int j = minZ-2; j < maxZ+2; j++) {
				createChunkBlocks(i, j);
			}
		}
		lock.unlock();
		for (int i = minX; i < maxX; i++) {
			for (int j = minZ; j < maxZ; j++) {
				createChunkMesh(i, j);
			}
		}
		
	}
	
}

void ChunkController::chunkGeneration()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	int maxX = chunkPos.x + RENDER_DISTANCE + 2;
	int minX = chunkPos.x - RENDER_DISTANCE - 2;
	int maxZ = chunkPos.z + RENDER_DISTANCE + 2;
	int minZ = chunkPos.z - RENDER_DISTANCE - 2;
	for (int i = minX; i < maxX; i++) {
		for (int j = minZ; j < maxZ; j++) {
			createChunk(i, j);
		}
	}
}

void ChunkController::chunkDegeneration()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	int maxX = chunkPos.x + RENDER_DISTANCE + 3;
	int minX = chunkPos.x - RENDER_DISTANCE - 3;
	int maxZ = chunkPos.z + RENDER_DISTANCE + 3;
	int minZ = chunkPos.z - RENDER_DISTANCE - 3;
	for (int i = minX; i < maxX; i++) {
		removeChunk(i, maxZ);
		removeChunk(i, minZ);
	}
	for (int j = minZ; j < maxZ; j++) {
		removeChunk(maxX, j);
		removeChunk(minX, j);
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

MeshBuilder* ChunkController::getMeshBuilder()
{
	return mb;
}


ChunkController::ChunkController(World* world, MeshBuilder* mb)
{
	this->world = world;
	this->mb = mb;
	pn = TerrainNoise();
	tg = new TreeGeneration();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	chunkLoadThread = std::thread(&ChunkController::chunkMeshGeneration, this);
}
