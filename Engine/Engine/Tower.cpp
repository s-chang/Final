#include "Tower.h"


Tower::Tower(void)
{
}


Tower::~Tower(void)
{
}

Tower* Tower::instance()
{
	static Tower tower;
	return &tower;
}

void Tower::init()
{
	currentFloor = Town::instance()->getFloor();
}

void Tower::shutdown()
{
}

int Tower::update()
{
	return BATTLE;
}
void Tower::render()
{
}