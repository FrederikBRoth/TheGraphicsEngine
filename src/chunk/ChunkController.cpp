#include <chunk/ChunkController.h>
#include <helpers/RenderDistance.h>

void ChunkController::createChunk(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);
	if (!chunkExists(key)) {
		glm::vec3 position = glm::vec3(x * CHUNKSIZE_X, 0.0f, z * CHUNKSIZE_Z);
		Chunk* newChunk = new Chunk(position);
		newChunk->createPerlinNoiseChunk(pn.generateNoiseMap(position, 20, 0.025), tg);
		chunkMap.insert(std::make_pair(key, newChunk));
	}
}

void ChunkController::createChunkMesh(int x, int z)
{
	VectorXZ key = tge::getKey(x, z);
	std::unique_lock<std::mutex> lock(generationMutex);
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

bool ChunkController::removeBlock(int x, int y, int z)
{
	glm::ivec3 worldPos = glm::ivec3(x, y, z);
	glm::ivec3 chunkPos = getChunkPosition(worldPos);
	VectorXZ key = tge::getKey(chunkPos.x, chunkPos.z);
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
			//std::unique_lock<std::mutex> lock(generationMutex);
			mb->updateChunkMesh(key, &chunkMap);
			return true;
		}
	}
	return false;
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

void ChunkController::update()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	std::unique_lock<std::mutex> lock(generationMutex);
	chunkGeneration();
	lock.unlock();
	for (auto& chunkMesh : mb->chunkMap) {
		if (chunkMesh.second->doBind) {
			chunkMesh.second->bind();
			chunkMesh.second->doBind = { false };
		}
		chunkMesh.second->draw();
	}
	chunkDegeneration();

}

ChunkController::ChunkController(World* world)
{
	this->world = world;
	this->mb = new MeshBuilder(world);
	pn = TerrainNoise();
	tg = new TreeGeneration();
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	chunkLoadThread = std::thread(&ChunkController::chunkMeshGeneration, this);
}
