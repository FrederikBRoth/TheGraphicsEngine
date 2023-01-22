#ifndef TREEGEN_H
#define TREEGEN_H
#include <chunk/Chunk.h>
struct TreeBlock {
	glm::ivec3 relativePos;
	BlockType type;
	TreeBlock(glm::ivec3 relativePos, BlockType) {
		this->relativePos = relativePos;
		this->type = type;
	}
};
class TreeGeneration
{
	const std::vector<TreeBlock> treeStructure{

		
	};
private:
	Chunk* currentChunk;
	std::vector<glm::ivec3> makeTreeStructure(glm::ivec3 root);
};
#endif
