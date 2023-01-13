#ifndef CHUNKCTRL_H
#define CHUNKCTRL_H
#include <unordered_map>
#include <chunk/Chunk.h>
#include <chunk/ChunkGenerator.h>

class ChunkController
{
private:
	World* world;
	ChunkGenerator* cg;
public:
	std::unordered_map<std::string, Chunk*> chunkMap;
	void createChunk(int x, int z);
	void updateBlock(int x, int y, int z);
	void update();
	std::string getKey(int x, int y);
	bool chunkExists(std::string);
	void chunkGenerationInfinite();
	ChunkController(World* world);
};
#endif // !1
