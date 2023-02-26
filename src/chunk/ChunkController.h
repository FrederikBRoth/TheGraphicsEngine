
#ifndef CHUNKCTRL_H
#define CHUNKCTRL_H
#include <unordered_map>
#include <chunk/Chunk.h>
#include <chunk/MeshBuilder.h>
#include <world/WorldUtils.h>
#include <thread>
#include <mutex>

class ChunkController
{
private:
	World* world;
	MeshBuilder* mb;
	TerrainNoise pn;
	//will become BiomeController or something about biomes in the future
	TreeGeneration* tg;
	std::thread chunkLoadThread;
	std::mutex generationMutex;
	std::atomic<bool> isRunning{ true };
public:
	ChunkController(World* world, MeshBuilder* mb);
	std::unordered_map<VectorXZ, Chunk*> chunkMap;
	void createChunk(int x, int z);
	void createChunkBlocks(int x, int z);
	void createChunkMesh(int x, int z);
	void updateChunk(int x, int y, int z);
	void removeChunk(int x, int z);
	BlockType removeBlock(int x, int y, int z);
	Block* getBlock(int x, int y, int z);
	Block* getBlock(int index, VectorXZ key);
	void updateBlock(int x, int y, int z, glm::vec3 relative, BlockType type);
	void updateChunkEdges(int x, int z, VectorXZ key);
	bool chunkExists(VectorXZ key);
	void chunkMeshGeneration();
	void chunkGeneration();
	void chunkDegeneration();
	glm::vec3 getChunkPosition(glm::vec3 position);
	MeshBuilder* getMeshBuilder();
};
#endif // !1
