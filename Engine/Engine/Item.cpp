#include "Item.h"

Item::Item()
{
	stats.name = "Nothing";
	stats.description = "Nothing";
	stats.type = "Nothing";
	stats.health = stats.atk = stats.mag = stats.def = stats.res = stats.spd = stats.level = stats.price = stats.xp = 0;
}

Item::~Item()
{}

Item::Item(ItemStats stats)
{
	setStats(stats);
	amount = 1;
}

void Item::use()
{}

ItemStats Item::getStats()
{
	return stats;
}

void Item::setStats(ItemStats itemStats)
{
	stats.atk = itemStats.atk;
	stats.def = itemStats.def;
	stats.mag = itemStats.mag;
	stats.res = itemStats.res;
	stats.spd = itemStats.spd;
	stats.health = itemStats.health;
	stats.name = itemStats.name;
	stats.description = itemStats.description;
	stats.type = itemStats.type;
	stats.level = itemStats.level;
	stats.price = itemStats.price;
	stats.xp = itemStats.xp;
}

void Item::setAmount(int num)
{
	amount = num;
}

int Item::getAmount()
{
	return amount;
}