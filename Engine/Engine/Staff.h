#pragma once

#include "Equippable.h"

class Staff : public Equippable
{
private:
public:
	Staff();
	Staff(ItemStats stats);
	~Staff();

	virtual void use();
};