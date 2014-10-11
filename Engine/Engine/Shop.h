#pragma once
#include "gamestate.h"

#define TABS 7 

struct SHOP_STATE
{
	static const int 
		OPEN = 0,
		BUY = 1,
		DISPLAY_ITEMS = 2,
		SELL = 3;
};

class Shop :
	public GameState
{
private:
	int state;
	bool help;
	Drawable bg;
	Drawable openWindow;
	Drawable ItemWindow;

	std::vector<Drawable> buttons;
	std::vector<Drawable> tabs;
	std::vector<Drawable> items;

	void setItems();

	Shop(void);
public:
	static Shop* instance();
	~Shop(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

