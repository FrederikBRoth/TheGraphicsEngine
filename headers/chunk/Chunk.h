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
#include <chunk/terrain-generation/PerlinNoise.hpp>
class Chunk
{
private:
	static const siv::PerlinNoise::seed_type seed = 123456u;

	static const siv::PerlinNoise perlin;
	void generateNoiseMap(std::vector<int>& noiseMap, glm::vec3& position);
public:
	glm::vec3 position;
	std::vector<Block*> chunk;
	std::vector<int> noiseMap;
	Chunk(glm::vec3 location);

	~Chunk();
	void createHalfChunk();
	void createSolidChunk();
	void createPseudoRealChunk();
	void createHollowCube();
	void createStairsChunk();

	
};
#endif // !CHUNK_H
