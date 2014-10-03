#pragma once

#include "Equippable.h"

class Spear: public Equippable
{
private:

public:
	Spear();
	Spear(ItemStats stats);
	~Spear();

	
	virtual void use();

};