#ifndef CHUNK_H
#define CHUNK_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <includes/chunk/Block.h>
#include <vector>
#include <includes/rendering/RenderInformation.h>
class Chunk
{
static const int CHUNKSIZE_X = 30;
static const int CHUNKSIZE_Y = 30;
static const int CHUNKSIZE_Z = 30;
public:
	glm::vec3 location;
	std::vector<std::vector<std::vector<Block*>>> chunk;
	Chunk(glm::vec3 location);
	~Chunk();
	void createSolidChunk();
	RenderInformation getMesh();
};
#endif // !CHUNK_H
