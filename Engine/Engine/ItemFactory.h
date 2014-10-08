#pragma once

#include "Item.h"
#include "Equippable.h"
#include "Staff.h"
#include "Spear.h"
#include "Accessory.h"
#include "Armor.h"
#include "Dagger.h"
#include "Rune.h"
#include <string>
#include <vector>

class ItemFactory
{
private:
	ItemFactory();
	std::vector<Item> itemlist;

	Item searchItem(std::string name);

	void loadList(const std::string filename);

public:
	static ItemFactory *instance();
	~ItemFactory();

	void loadFactory();

	Item *getItem(std::string name);
};

