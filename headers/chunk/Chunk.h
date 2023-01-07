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
	static const int CHUNKSIZE_X = 16;
	static const int CHUNKSIZE_Y = 16;
	static const int CHUNKSIZE_Z = 16;

	glm::vec3 position;
	std::vector<std::vector<std::vector<Block*>>> chunk;
	Chunk(glm::vec3 location);
	~Chunk();
	void createSolidChunk();
	void createStripePattern();
};
#endif // !CHUNK_H
