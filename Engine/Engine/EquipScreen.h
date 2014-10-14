#pragma once
#include "gamestate.h"
#include "Item.h"

struct EQUIPSTATE{
	static const int
		START = 0,
		SHOW_ITEMS = 1,
		SHOW_AVAILABLE = 2;
};

class EquipScreen :
	public GameState
{
private:
	Drawable background,
		background2,
		background3;
	std::vector<Drawable> buttons;
	std::vector<Drawable> equipped;
	std::vector<Drawable> available;

	int who, state, slot;

	EquipScreen(void);
	void displayItemStats(bool top, Item* item);
	void setItems(int who);
	void setAvailable(int who, int slot);
public:
	static EquipScreen* instance();
	~EquipScreen(void);

	void init();
	void shutdown();

	int update();
	void render();

	void setState(int state);
};