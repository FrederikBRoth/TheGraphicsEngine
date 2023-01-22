#ifndef CHUNKCTRL_H
#define CHUNKCTRL_H
#include <unordered_map>
#include <chunk/Chunk.h>
#include <chunk/ChunkGenerator.h>
#include <world/WorldUtils.h>
#include <thread>
#include <mutex>

class ChunkController
{
private:
	World* world;
	ChunkGenerator* cg;
	TerrainNoise pn;
	std::thread chunkLoadThread;
	std::mutex generationMutex;
	std::atomic<bool> isRunning{ true };
public:
	std::unordered_map<std::string, Chunk*> chunkMap;
	void createChunk(int x, int z);
	void createChunkMesh(int x, int z);
	void updateChunk(int x, int y, int z);
	void removeChunk(int x, int z);
	bool removeBlock(int x, int y, int z);

	void update();
	std::string getKey(int x, int y);
	bool chunkExists(std::string);
	void chunkMeshGeneration();
	void chunkGeneration();
	void chunkDegeneration();
	glm::vec3 getChunkPosition(glm::vec3 position);
	ChunkController(World* world);
};
#endif // !1
