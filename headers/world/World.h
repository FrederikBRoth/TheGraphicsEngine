#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <chunk/Chunk.h>

constexpr int CHUNKSIZE_X = 16, CHUNKSIZE_Y = 16, CHUNKSIZE_Z = 16, CHUNKAREA = CHUNKSIZE_X * CHUNKSIZE_Y,
CHUNKVOLUME = CHUNKAREA * CHUNKSIZE_Z, WATER_LEVEL = 64;
class World
{

	//std::vector<Chunk*> chunks;
};
#endif // !WORLD_H
