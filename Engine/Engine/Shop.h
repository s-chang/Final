#pragma once
#include "gamestate.h"
#include "Item.h"

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
	bool help,
		insufficientFunds;
	std::string helpText;

	Drawable bg;
	Drawable openWindow;
	Drawable ItemWindow;

	std::vector<Drawable> buttons;
	std::vector<Drawable> tabs;
	std::vector<Drawable> items;

	void Spears();
	void Daggers();
	void Staves();
	void Armor();
	void Accessories();
	void Runes(); 
	void Consumables();

	void checkItems();
	int checkList(std::vector<Drawable>&);
	void displayItemStats(Item* item);

	Shop(void);
public:
	static Shop* instance();
	~Shop(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

