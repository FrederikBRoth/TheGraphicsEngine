#include <chunk/Block.h>

Block::Block(BlockType type)
{
	if (type == BlockType::AIR || type == BlockType::WATER) {
		this->isCollidable = false;
	}
	else {
		this->isCollidable = true;
	}
	this->type = type;
}


