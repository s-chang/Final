#pragma once

#include "Equippable.h"

class Dagger : public Equippable
{
private:

public:
	Dagger();
	Dagger(ItemStats stats);
	~Dagger();

	virtual void use();

};