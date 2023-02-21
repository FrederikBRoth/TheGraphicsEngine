
#ifndef INVENTORY_H
#define INVENTORY_H
#include <world/WorldUtils.h>
#include <chunk/Block.h>
#include <map>
class Inventory
{
public:
	const int inventorySize = 10;
	std::vector<BlockType> inventory;
	std::map<BlockType, int> storage;
	int selected;
	void addItem(BlockType type);
	void removeItem();
	void cycleSelection(int incr);
	Inventory();
};
#endif // !INVENTORY_H
