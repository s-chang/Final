#pragma once
#include "gamestate.h"

#define SHOP_BUTTONS 1

class Shop :
	public GameState
{
private:
	Drawable bg,
			 box;
	Drawable buttons[SHOP_BUTTONS];

	Shop(void);
public:
	static Shop* instance();
	~Shop(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

