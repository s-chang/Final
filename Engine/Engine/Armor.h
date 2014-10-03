#pragma once

#include "Equippable.h"

class Armor : public Equippable
{
private:
public:
	Armor();
	Armor(ItemStats stats);
	~Armor();

	virtual void use();
};