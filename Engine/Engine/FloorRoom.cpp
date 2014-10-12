#include "FloorRoom.h"

FloorRoom::FloorRoom()
{}

FloorRoom::~FloorRoom()
{}

void FloorRoom::init(std::string handle)
{
	setHandle("room");
	name = handle;
	set3D(true);
}

void FloorRoom::setArrival(bool arg)
{
	arrival = arg;
}

void FloorRoom::setTreasure(bool arg)
{
	treasure = arg;
}

void FloorRoom::setStairs(bool arg)
{
	stairs = arg;
}

bool FloorRoom::getArrival()
{
	return arrival;
}

bool FloorRoom::getTreasure()
{
	return treasure;
}

bool FloorRoom::getStairs()
{
	return stairs;
}

void FloorRoom::setName(std::string name)
{
	this->name = name;
}

std::string FloorRoom::getName()
{
	return name;
}