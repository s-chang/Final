#pragma once
#include "gamestate.h"
#include "Item.h"
#include "Entity.h"

struct INV_STATES{
	static const int
		START = 0,
		USE = 1,
		SELECT_CHAR = 2,
		SORT = 3;
};

class InventoryScreen :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> buttons;
	std::vector<Drawable> items;

	int state;
	Item * useThis;

	void useItem(Entity* onThisGuy);
	void checkItems();

	void displayHPandResource();
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