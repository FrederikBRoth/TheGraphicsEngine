
#ifndef INVENTORY_H
#define INVENTORY_H
#include <world/WorldUtils.h>
#include <chunk/Block.h>
#include <map>
class Inventory
{
private:
	std::map<BlockType, int> storage;
public:
	BlockType selected;
	void addItem(BlockType type);
	void removeItem(BlockType type);
	Inventory();
};
#endif // !INVENTORY_H
