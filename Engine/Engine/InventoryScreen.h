#pragma once
#include "gamestate.h"
class InventoryScreen :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> buttons;
	std::vector<Drawable> items;
	bool getNewList;

	InventoryScreen(void);
public:
	static InventoryScreen* instance();
	~InventoryScreen(void);

	void init();
	void shutdown();

	int update();
	void render();

	void resetList();
	void setBool(bool);
};