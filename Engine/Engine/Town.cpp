#include "Town.h"


Town::Town(void) : GameState()
{
}

Town* Town::instance()
{
	static Town t;
	return &t;
}

Town::~Town(void)
{
}

void Town::init()
{
}

void Town::shutdown()
{
}

int Town::update()
{
	return 0;
}
void Town::render()
{
}