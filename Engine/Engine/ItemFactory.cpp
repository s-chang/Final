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
	if(name == "Weathered Spear")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Short Spear")
	{
		
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Spear")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Harpoon")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Lance")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Gae Bolg")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Luin of Celtchar")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Gungnir")
	{
		return new Spear(searchItem(name).getStats());
	}

	if(name == "Chipped Dagger")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Knife")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Sting")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Needle")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Dagger")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Night's Bane")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Shiv of Titans")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Death and Deceit")
	{
		return new Dagger(searchItem(name).getStats());
	}

	if(name == "Splintered Staff")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Rod")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Staff")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Rod of Light")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Staff of Wisdom")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Iron Staff")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Staff of the Ancients")
	{
		return new Staff(searchItem(name).getStats());
	}
	if(name == "Save the Queen")
	{
		return new Staff(searchItem(name).getStats());
	}

	return new Item();


}

void ItemFactory::loadFactory()
{
	ItemStats tempStats;


	std::ifstream file("Spear.txt");

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

	std::ifstream file2("Dagger.txt");

	while(std::getline(file2, tempStats.name, ','))
	{
		std::string tempInt;
		
		std::getline(file2, tempStats.type, ',');
		std::getline(file2, tempStats.description, ',');

		std::getline(file2, tempInt, ',');
		tempStats.level = (int)atoi(tempInt.c_str());

		std::getline(file2, tempInt, ',');
		tempStats.health = (int)atoi(tempInt.c_str());

		std::getline(file2, tempInt, ',');
		tempStats.atk = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt, ',');
		tempStats.mag = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt, ',');
		tempStats.def = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt, ',');
		tempStats.res = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt, ',');
		tempStats.spd = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt, ',');
		tempStats.price = (int)atoi(tempInt.c_str());

			std::getline(file2, tempInt);
		tempStats.xp = (int)atoi(tempInt.c_str());
		

		itemlist.push_back(Item(tempStats));
	}

	file2.close();

	std::ifstream file3("Staff.txt");

	while(std::getline(file3, tempStats.name, ','))
	{
		std::string tempInt;
		
		std::getline(file3, tempStats.type, ',');
		std::getline(file3, tempStats.description, ',');

		std::getline(file3, tempInt, ',');
		tempStats.level = (int)atoi(tempInt.c_str());

		std::getline(file3, tempInt, ',');
		tempStats.health = (int)atoi(tempInt.c_str());

		std::getline(file3, tempInt, ',');
		tempStats.atk = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt, ',');
		tempStats.mag = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt, ',');
		tempStats.def = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt, ',');
		tempStats.res = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt, ',');
		tempStats.spd = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt, ',');
		tempStats.price = (int)atoi(tempInt.c_str());

			std::getline(file3, tempInt);
		tempStats.xp = (int)atoi(tempInt.c_str());
		

		itemlist.push_back(Item(tempStats));
	}

	file3.close();
}