#ifndef CHUNK_H
#define CHUNK_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chunk/Block.h>
#include <vector>
#include <rendering/RenderInformation.h>
#include <array>
#include <world/Constants.h>
#include <chunk/terrain-generation/PerlinNoise.h>

class Chunk
{
private:

public:
	glm::vec3 position;
	std::vector<Block*> chunk;
	Chunk(glm::vec3 location);

	~Chunk();
	void createHalfChunk();
	void createSolidChunk();
	void createPerlinNoiseChunk(std::vector<int>& noiseMap);
	void createHollowCube();
	void createStairsChunk();

	
};
#endif // !CHUNK_H
