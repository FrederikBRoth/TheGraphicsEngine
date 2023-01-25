#include <chunk/terrain-generation/TreeGeneration.h>
#include <chunk/Chunk.h>


void TreeGeneration::placeTree(glm::ivec3 root, Chunk* chunk)
{
	for (auto& treeBlock : treeStructure) {
		chunk->changeBlock(root + treeBlock.relativePos, treeBlock.type);
	}
}

TreeGeneration::TreeGeneration()
{
}
