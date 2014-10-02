#pragma once

#include "Equippable.h"

class Rune: public Equippable
{
private:
public:
	Rune();
	~Rune();
	Rune(ItemStats stats);

	virtual void use();

};