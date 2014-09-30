#pragma once
#include "entity.h"
#include <vector>
class Lenn :
	public Entity
{
private:
	int stamina, staminaMax;
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

	Lenn(void);
public:
	static Lenn* instance();
	~Lenn(void);

	void init();
	void levelUp();

	int getResource() { return stamina; }
	int getMaxResource() { return staminaMax; }
	int getXpToLevel(){ return xpToLevel; }
	std::string getCommand(int index){ return commands[index]; };
};

