#ifndef CHUNK_H
#define CHUNK_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chunk/Block.h>
#include <vector>
#include <rendering/RenderInformation.h>
#include <array>
class Chunk
{
public:
	const int CHUNKSIZE_X;
	const int CHUNKSIZE_Y;
	const int CHUNKSIZE_Z;
	const int CHUNKAREA = CHUNKSIZE_X * CHUNKSIZE_Y;
	const int CHUNKVOLUME = CHUNKAREA * CHUNKSIZE_Z;

	glm::vec3 position;
	std::vector<Block*> chunk;
	Chunk(glm::vec3 location);
	Chunk(glm::vec3 location, int x, int y, int z);

	~Chunk();
	void createSolidChunk();
	void createStripePatternChunk();
	void createStairsChunk();
	int getIndex(int x, int y, int z);

	
};
#endif // !CHUNK_H
