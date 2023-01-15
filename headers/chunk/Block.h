#ifndef BLOCK_H
#define BLOCK_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <texturing/TextureCoords.h>
#include <texturing/TextureMap.h>
enum class BlockType {
	GRASS,
	STONE,
	DIRT,
	AIR
};
enum class FaceType {
	GRASS_TOP,
	GRASS_SIDE,
	STONE,
	DIRT
};

class Block
{
public:
	BlockType type;
	Block(BlockType type);
};
#endif // !BLOCK_H
