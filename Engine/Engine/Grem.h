#pragma once
#include "entity.h"
#include <vector>
class Grem :
	public Entity
{
private:

	int rage, rageMax;
	int xpToLevel;
	/*Equippable * weapon;
	Equippable * armor;
	Equippable * accessory1;
	Equippable * accessory2;

	std::vector<Command*> skills;

	Command *one;
	Command *two;
	Command *three;
	Command *four;*/

	std::string commands[4];
	std::vector<std::string> skills;

	Grem(void);
public:
	static Grem* instance();
	~Grem(void);

	void init();
	void levelUp();

	int getResource() { return rage; }
	int getMaxResource() { return rageMax; }
	int getXpToLevel(){ return xpToLevel; }
	std::string getCommand(int index){ return commands[index]; };
};

