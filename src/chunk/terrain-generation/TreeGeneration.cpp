#include <chunk/terrain-generation/TreeGeneration.h>
#include <chunk/Chunk.h>


void TreeGeneration::placeTree(glm::ivec3 root, std::vector<Block*>& blocks)
{
	for (auto& treeBlock : treeStructure) {
		glm::ivec3 pos = root + treeBlock.relativePos;
		delete blocks[tge::getIndex(pos.x, pos.y, pos.z)];
		blocks[tge::getIndex(pos.x, pos.y, pos.z)] = new Block(treeBlock.type);
	}
}

const std::vector<TreeBlock>& TreeGeneration::getTreeStructure()
{
	return treeStructure;
}

TreeGeneration::TreeGeneration()
{
}
