#include <controls/player/Inventory.h>

void Inventory::addItem(BlockType type)
{
	if (!storage.count(type))
		storage.insert(std::pair(type, 0));
	storage[type]++;
	std::cout << tge::getBlockName(type) << ": " << storage[type] << std::endl;
}

void Inventory::removeItem(BlockType type)
{
	if (storage.count(type)) {
		if(storage[type] != 0)
			storage[type]--;
	}
}

Inventory::Inventory()
{
	selected = BlockType::GRASS;
}

