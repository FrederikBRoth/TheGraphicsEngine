#ifndef TREEGEN_H
#define TREEGEN_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chunk/Block.h>


struct TreeBlock {
	glm::ivec3 relativePos;
	BlockType type;
	TreeBlock(glm::ivec3 relativePos, BlockType type) {
		this->relativePos = relativePos;
		this->type = type;
	}
};
class Chunk;

class TreeGeneration
{
	//temp tree gen, should have a decent pipeline of imborting objs/json of blocks and do that
	const std::vector<TreeBlock> treeStructure{
		TreeBlock({0,0,0}, BlockType::WOOD),
		TreeBlock({0,1,0}, BlockType::WOOD),
		TreeBlock({0,2,0}, BlockType::WOOD),
		TreeBlock({0,3,0}, BlockType::WOOD),
		TreeBlock({0,4,0}, BlockType::WOOD),
		//First leaf layer
		//TreeBlock({-2, 4, -2}, BlockType::LEAF),
		TreeBlock({-2, 4, -1}, BlockType::LEAF),
		TreeBlock({-2, 4, 0}, BlockType::LEAF),
		TreeBlock({-2, 4, 1}, BlockType::LEAF),
		//TreeBlock({-2, 4, 2}, BlockType::LEAF),
		TreeBlock({-1, 4, -2}, BlockType::LEAF),
		TreeBlock({-1, 4, -1}, BlockType::LEAF),
		TreeBlock({-1, 4, 0}, BlockType::LEAF),
		TreeBlock({-1, 4, 1}, BlockType::LEAF),
		TreeBlock({-1, 4, 2}, BlockType::LEAF),
		TreeBlock({0, 4, -2}, BlockType::LEAF),
		TreeBlock({0, 4, -1}, BlockType::LEAF),
		//TreeBlock({0, 4, 0}, BlockType::LEAF),
		TreeBlock({0, 4, 1}, BlockType::LEAF),
		TreeBlock({0, 4, 2}, BlockType::LEAF),
		TreeBlock({1, 4, -2}, BlockType::LEAF),
		TreeBlock({1, 4, -1}, BlockType::LEAF),
		TreeBlock({1, 4, 0}, BlockType::LEAF),
		TreeBlock({1, 4, 1}, BlockType::LEAF),
		TreeBlock({1, 4, 2}, BlockType::LEAF),
		//TreeBlock({2, 4, -2}, BlockType::LEAF),
		TreeBlock({2, 4, -1}, BlockType::LEAF),
		TreeBlock({2, 4, 0}, BlockType::LEAF),
		TreeBlock({2, 4, 1}, BlockType::LEAF),
		//TreeBlock({2, 4, 2}, BlockType::LEAF),
		//Second leaf layer
		//TreeBlock({-2, 5, -2}, BlockType::LEAF),
		TreeBlock({-2, 5, -1}, BlockType::LEAF),
		TreeBlock({-2, 5, 0}, BlockType::LEAF),
		TreeBlock({-2, 5, 1}, BlockType::LEAF),
		//TreeBlock({-2, 5, 2}, BlockType::LEAF),
		TreeBlock({-1, 5, -2}, BlockType::LEAF),
		TreeBlock({-1, 5, -1}, BlockType::LEAF),
		TreeBlock({-1, 5, 0}, BlockType::LEAF),
		TreeBlock({-1, 5, 1}, BlockType::LEAF),
		TreeBlock({-1, 5, 2}, BlockType::LEAF),
		TreeBlock({0, 5, -2}, BlockType::LEAF),
		TreeBlock({0, 5, -1}, BlockType::LEAF),
		TreeBlock({0, 5, 0}, BlockType::LEAF),
		TreeBlock({0, 5, 1}, BlockType::LEAF),
		TreeBlock({0, 5, 2}, BlockType::LEAF),
		TreeBlock({1, 5, -2}, BlockType::LEAF),
		TreeBlock({1, 5, -1}, BlockType::LEAF),
		TreeBlock({1, 5, 0}, BlockType::LEAF),
		TreeBlock({1, 5, 1}, BlockType::LEAF),
		TreeBlock({1, 5, 2}, BlockType::LEAF),
		//TreeBlock({2, 5, -2}, BlockType::LEAF),
		TreeBlock({2, 5, -1}, BlockType::LEAF),
		TreeBlock({2, 5, 0}, BlockType::LEAF),
		TreeBlock({2, 5, 1}, BlockType::LEAF),
		//TreeBlock({2, 4, 2}, BlockType::LEAF),
		//Smaller top
		TreeBlock({-1, 6, -1}, BlockType::LEAF),
		TreeBlock({-1, 6, 0}, BlockType::LEAF),
		TreeBlock({-1, 6, 1}, BlockType::LEAF),
		TreeBlock({0, 6, -1}, BlockType::LEAF),
		TreeBlock({0, 6, 0}, BlockType::LEAF),
		TreeBlock({0, 6, 1}, BlockType::LEAF),
		TreeBlock({1, 6, -1}, BlockType::LEAF),
		TreeBlock({1, 6, 0}, BlockType::LEAF),
		TreeBlock({1, 6, 1}, BlockType::LEAF),
		//smallest top
		TreeBlock({-1, 7, 0}, BlockType::LEAF),
		TreeBlock({0, 7, 1}, BlockType::LEAF),
		TreeBlock({0, 7, 0}, BlockType::LEAF),
		TreeBlock({0, 7, -1}, BlockType::LEAF),
		TreeBlock({1, 7, 0}, BlockType::LEAF)
	};
public:
	void placeTree(glm::ivec3 root, std::vector<Block*>& blocks);
	const std::vector<TreeBlock>& getTreeStructure();
	TreeGeneration();

};
#endif
