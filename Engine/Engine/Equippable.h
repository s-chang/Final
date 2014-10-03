#pragma once
#include <string>

#include "Item.h"


class Equippable : public Item
{
private:
	

public:
	Equippable();
	Equippable(ItemStats stats);
	~Equippable();

	virtual void use();


};