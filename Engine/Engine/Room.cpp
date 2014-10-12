#include "Room.h"
#include <stdlib.h>

Room::Room()
{
	arrival = false;
	treasure = false;
	stairs = false;
}

Room::~Room()
{}

void Room::setRoom(Corridor room, bool treasure, bool stairs)
{
	this->treasure = treasure;
	this->stairs = stairs;
	setIcon(room.getIcon());
	setX(room.getX());
	setY(room.getY());
}

void Room::setTreasure(bool arg)
{
	treasure = arg;
}

void Room::setStairs(bool arg)
{
	stairs = arg;
}

bool Room::getTreasure()
{
	return treasure;
}

bool Room::getStairs()
{
	return stairs;
}

void Room::init()
{
	int temp = rand() % 2;

	if(temp == 1)
		treasure = true;
}

void Room::setArrival(bool arg)
{
	arrival = arg;
}

bool Room::getArrival()
{
	return arrival;
}