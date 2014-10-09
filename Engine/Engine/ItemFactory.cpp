#include "ItemFactory.h"
#include <fstream>
#include <sstream>

ItemFactory::ItemFactory()
{}


ItemFactory::~ItemFactory()
{}

ItemFactory *ItemFactory::instance()
{
	static ItemFactory factory;
	return &factory;
}

Item ItemFactory::searchItem(std::string name)
{
	for(unsigned int i = 0; i < itemlist.size(); i++)
	{
		if(name == itemlist[i].getStats().name)
			return itemlist[i];
	}
	return Item();
}

Item *ItemFactory::getItem(std::string name)
{
	Item temp(searchItem(name).getStats());

	if(temp.getStats().type == "Spear")
	{
		return new Spear(temp.getStats());
	}

	if(temp.getStats().type == "Dagger")
	{
		return new Dagger(temp.getStats());
	}

	if(temp.getStats().type == "Staff")
	{
		return new Staff(temp.getStats());
	}

	if(temp.getStats().type == "Armor")
	{
		return new Armor(temp.getStats());
	}

	if(temp.getStats().type == "Rune")
	{
		return new Rune(temp.getStats());
	}

	if(temp.getStats().type == "Item")
	{
		return new Item(temp.getStats());
	}

	if(temp.getStats().type == "Accessory")
	{
		return new Accessory(temp.getStats());
	}

	return new Item();

}

void ItemFactory::loadList(const std::string filename)
{
	ItemStats tempStats;

	std::ifstream file(filename);
	while(std::getline(file, tempStats.name, ','))
	{
		std::string tempInt;

		std::getline(file, tempStats.type, ',');
		std::getline(file, tempStats.description, ',');

		std::getline(file, tempInt, ',');
		tempStats.level = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.health = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.atk = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.mag = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.def = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.res = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.spd = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt, ',');
		tempStats.price = (int)atoi(tempInt.c_str());

		std::getline(file, tempInt);
		tempStats.xp = (int)atoi(tempInt.c_str());


		itemlist.push_back(Item(tempStats));
	}

	file.close();

}

void ItemFactory::loadFactory()
{

	loadList("Spear.txt");
	loadList("Dagger.txt");
	loadList("Staff.txt");
	loadList("Item.txt");
	loadList("Armor.txt");
	
}