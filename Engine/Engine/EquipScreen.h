#pragma once
#include "gamestate.h"

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
	Drawable background;
	std::vector<Drawable> buttons;
	std::vector<Drawable> equipped;
	std::vector<Drawable> available;
	int who, state, slot;

	EquipScreen(void);
	void displayItemStats(bool top);
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