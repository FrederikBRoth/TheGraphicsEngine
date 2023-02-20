#include <gui\gui-elements\InventoryGui.h>

InventoryGui::InventoryGui(ScreenText* st, Player* player)
{
	this->st = st;
	this->player = player;
}

void InventoryGui::renderGui()
{
	std::string blockName = tge::getBlockName(player->inventory->selected);
	st->renderText(blockName, 500, 500, 1.0, glm::vec3(1, 1, 1));
}
