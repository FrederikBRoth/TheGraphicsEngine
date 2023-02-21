#include <gui\gui-elements\InventoryGui.h>

InventoryGui::InventoryGui(ScreenText* st, Player* player)
{
	this->st = st;
	this->player = player;
}

void InventoryGui::renderGui()
{
	int start = 300;
	int widthIncr = (SCREEN_WIDTH - start*2) / player->inventory->inventorySize;
	int incr = 45;
	int i = 0;
	for (auto& block : player->inventory->inventory) {
		std::string name = tge::getBlockName(block);
		if (i == player->inventory->selected) {
			st->renderText(name, start + (30 - (name.size() * 3)), 100, 0.5, glm::vec3(1, 1, 1));
			st->renderText(std::to_string(player->inventory->storage[block]), start + 40, 70, 0.5, glm::vec3(1, 1, 1));
			st->renderText("V", start + 40, 130, 0.5, glm::vec3(1, 1, 1));
		}
		else {
			st->renderText(name, start + (30 - (name.size() * 3)), 100, 0.5, glm::vec3(1, 1, 1));
			st->renderText(std::to_string(player->inventory->storage[block]), start + 40, 70, 0.5, glm::vec3(1, 1, 1));
		}
		start += widthIncr;
		i++;
	};

}
