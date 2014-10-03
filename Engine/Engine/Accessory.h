#pragma once

#include "Equippable.h"

class Accessory : public Equippable
{
private:
public:
	Accessory();
	Accessory(ItemStats stats);
	~Accessory();
	virtual void use();
};