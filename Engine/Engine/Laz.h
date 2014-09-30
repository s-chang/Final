#pragma once
#include "entity.h"
#include <vector>
class Laz :
	public Entity
{
private:
	int mana, manaMax;
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

	Laz(void);
public:
	static Laz* instance();
	~Laz(void);

	void init();
	void levelUp();

	int getResource() { return mana; }
	int getMaxResource() { return manaMax; }
	int getXpToLevel(){ return xpToLevel; }
	std::string getCommand(int index){ return commands[index]; };
};

