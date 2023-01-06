#ifndef BLOCK_H
#define BLOCK_H
enum class BlockType {
	GRASS,
	STONE,
	AIR
};
class Block
{
public:
	BlockType type;
	Block(BlockType type);
};
#endif // !BLOCK_H
