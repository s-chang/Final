#include "Corridor.h"

Corridor::Corridor()
{}

Corridor::~Corridor()
{}

void Corridor::init()
{

}

void Corridor::setIcon(unsigned char icon)
{
	this->icon = icon;
}

unsigned char Corridor::getIcon()
{
	return icon;
}

void Corridor::setX(int x)
{
	this->x = x;
}

void Corridor::setY(int y)
{
	this->y = y;
}

void Corridor::setType(bool arg)
{
	type = arg;
}

int Corridor::getX()
{
	return x;
}

int Corridor::getY()
{
	return y;
}

bool Corridor::getType()
{
	return type;
}