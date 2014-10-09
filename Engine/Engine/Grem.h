#pragma once
#include "entity.h"
#include "CommandList.h"
#include "Spear.h"

class Grem :
	public Entity
{
private:

	int rage, rageMax;
	int xpToLevel;
	
	Spear* weapon;
	Armor* armor;
	Accessory* acc1,
			 * acc2;
	Rune* rune1,
		* rune2;

	BattleCommand* commands[4];
	
	Grem(void);
public:
	std::vector<BattleCommand*> availableCommands;
	std::vector<std::string> skills;

	static Grem* instance();
	~Grem(void);

	void init();
	void levelUp();

	int getResource() { return rage; }
	int getMaxResource() { return rageMax; }
	int getXpToLevel(){ return xpToLevel; }
	BattleCommand* getCommand(int index){ return commands[index]; };
	ItemStats* getItemStatsForSlot(int whatSlot);
	void addXP(int amount);
	void adjustResource(int amount);
};

