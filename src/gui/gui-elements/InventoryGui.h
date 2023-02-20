#include <gui/ScreenText.h>
#include <controls/player/Player.h>
#ifndef INVENTORY_GUI_H
#define INVENTORY_GUI_H

class InventoryGui
{
private:
	ScreenText* st;
	Player* player;
public:
	InventoryGui(ScreenText* st, Player* player);
	void renderGui();
};
#endif // !INVENTORY_GUI_H
