#include <controls/player/Inventory.h>

void Inventory::addItem(BlockType type)
{
	if (!storage.count(type)) {
		for (int i = 0; i < inventorySize; i++) {
			if (inventory[i] == BlockType::NOTHING) {
				inventory[i] = type;
				break;
			}
		}
		storage.insert(std::pair(type, 0));
	}
	storage[type]++;
}

BlockType Inventory::removeItem()
{

	BlockType type = inventory[selected];

	if (storage.count(type) && type != BlockType::NOTHING) {
		storage[type]--;
		if (storage[type] == 0) {
			storage.erase(type);
			inventory[selected] = BlockType::NOTHING;
		}
	}
	return type;
}

void Inventory::cycleSelection(int incr)
{
	selected = tge::modulus(selected + incr, inventorySize);
}

Inventory::Inventory()
{
	selected = 0;
	inventory = std::vector<BlockType>(inventorySize, BlockType::NOTHING);
}

