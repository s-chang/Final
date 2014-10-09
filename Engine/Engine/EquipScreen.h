#pragma once
#include "gamestate.h"
class EquipScreen :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> buttons;
	EquipScreen(void);
public:
	static EquipScreen* instance();
	~EquipScreen(void);

	void init();
	void shutdown();

	int update();
	void render();
};