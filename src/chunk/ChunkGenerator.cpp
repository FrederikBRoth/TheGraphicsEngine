#include <chunk/ChunkGenerator.h>

ChunkGenerator::ChunkGenerator(World* world)
{
	this->world = world;
}

bool ChunkGenerator::chunkExists(int x, int z)
{
	return chunkMap.count(makeMapKey(x, z));
}

void ChunkGenerator::createChunk()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();
	if (!chunkExists(chunkPos.x, chunkPos.z)) {
		Chunk* newChunk = new Chunk(glm::vec3((chunkPos.x)*CHUNKSIZE_X, -16.0f, (chunkPos.z) * CHUNKSIZE_Z));
		newChunk->createSolidChunk();
		TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
		ChunkBuilder cb = ChunkBuilder(tm->getTexCoords(0, 2));
		chunkMap.emplace(makeMapKey(chunkPos.x, chunkPos.z), new IndexedMesh((cb.getChunkMesh(newChunk))));
	}
}

void ChunkGenerator::createChunk(int x, int z)
{
	if (!chunkExists(x, z)) {
		Chunk* newChunk = new Chunk(glm::vec3((x) * CHUNKSIZE_X, -16.0f, (z) * CHUNKSIZE_Z));
		newChunk->createSolidChunk();
		TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
		ChunkBuilder cb = ChunkBuilder(tm->getTexCoords(2, 3));
		chunkMap.emplace(makeMapKey(x, z), new IndexedMesh((cb.getChunkMesh(newChunk))));
	}
}

void ChunkGenerator::update()
{
	glm::vec3 chunkPos = world->getChunkWorldPosition();

	infiniteTest();
	for (auto const& kv : chunkMap) {
		kv.second->render();
	} 
	std::cout << makeMapKey(chunkPos.x, chunkPos.z) << std::endl;
}

std::string ChunkGenerator::makeMapKey(int x, int z)
{
	std::string key = "x";
	key += std::to_string(x);
	key += "z";
	key += std::to_string(z);

	return key;
}

void ChunkGenerator::infiniteTest()
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




