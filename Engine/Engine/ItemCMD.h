#pragma once
#include "battlecommand.h"
#include "Item.h"
#include "Entity.h"

class ItemCMD :
	public BattleCommand
{
private:
	std::vector<Drawable> items;
	std::vector<Drawable> allyList;

	bool itemSelected;
	Item * useThis;

	void setList();
	void checkItems();
	void checkAllies();
	void useItem(Entity* onThisGuy);

public:
	ItemCMD(void);
	~ItemCMD(void);

	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};
