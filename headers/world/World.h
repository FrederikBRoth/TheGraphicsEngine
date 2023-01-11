#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <chunk/Chunk.h>
#include <glm/detail/type_vec3.hpp>
#include <math.h>
constexpr int CHUNKSIZE_X = 16, CHUNKSIZE_Y = 16, CHUNKSIZE_Z = 16, CHUNKAREA = CHUNKSIZE_X * CHUNKSIZE_Y,
CHUNKVOLUME = CHUNKAREA * CHUNKSIZE_Z, WATER_LEVEL = 64;
class World
{
	Chunk* chunks;
	int worldX, worldY, worldZ;
	void updateWorldPosition(float x, float y, float z);
	glm::u32vec3 getWorldPosition();
	void generateChunk();
	void update();
	
};
#endif // !WORLD_H
