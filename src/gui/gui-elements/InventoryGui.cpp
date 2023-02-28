#include <gui\gui-elements\InventoryGui.h>

InventoryGui::InventoryGui(ScreenText* st, Player* player)
{
	this->st = st;
	this->player = player;
}

void InventoryGui::renderGui()
{
	int start = 300;
	int height = 50;
	int widthIncr = (SCREEN_WIDTH - start*2) / player->inventory->inventorySize;
	int incr = 45;
	int i = 0;

	for (auto& block : player->inventory->inventory) {
		std::string name = tge::getBlockName(block);
		if (i == player->inventory->selected) {
			st->renderText(name, start + (30 - (name.size() * 3)), height, 0.5, glm::vec3(0.6, 0.6, 0.6));
			st->renderText(std::to_string(player->inventory->storage[block]), start + 40, height - 30, 0.5, glm::vec3(0.6, 0.6, 0.6));
			st->renderText("V", start + 40, height + 30, 0.5, glm::vec3(0.9, 0.84, 0.2));
		}
		else {
			st->renderText(name, start + (30 - (name.size() * 3)), height, 0.5, glm::vec3(0.6, 0.6, 0.6));
			st->renderText(std::to_string(player->inventory->storage[block]), start + 40, height-30, 0.5, glm::vec3(0.6, 0.6, 0.6));
		}
		start += widthIncr;
		i++;
	};

}
