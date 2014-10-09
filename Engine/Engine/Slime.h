#pragma once
#include "entity.h"

class Slime :
	public Entity
{
private:

public:
	Slime(void);
	~Slime(void);
	
	void init();
	void levelUp();

};

