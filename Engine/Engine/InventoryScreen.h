#pragma once
#include "gamestate.h"
class InventoryScreen :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> buttons;
	std::vector<Drawable> items;

	InventoryScreen(void);
public:
	static InventoryScreen* instance();
	~InventoryScreen(void);

	void init();
	void shutdown();

	int update();
	void render();

	void setList();
	void displayItem(int index);
};