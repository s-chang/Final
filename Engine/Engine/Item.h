#pragma once

#include <string>

struct ItemStats
{
	std::string name;
	std::string description;
	std::string type;
	int health, atk, mag, def, res, spd;
	int level;
	int price;
	int xp;
};

class Item
{
private:
	ItemStats stats;
	int amount;

public:
	Item();
	Item(ItemStats stats);
	~Item();

	virtual void use();

	ItemStats getStats();
	void setStats(ItemStats itemStats);


	void setAmount(int num);
	int getAmount();
};