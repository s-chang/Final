#pragma once
#include "entity.h"
#include "CommandList.h"
#include "Dagger.h"
#include <vector>
class Lenn :
	public Entity
{
private:
	int stamina, staminaMax;
	int xpToLevel;

	Dagger* weapon;
	Armor* armor;
	Accessory* acc1,
			 * acc2;
	Rune* rune1,
		* rune2;

	BattleCommand* commands[4];

	Lenn(void);
public:
	std::vector<BattleCommand*> availableCommands;
	std::vector<std::string> skills;

	static Lenn* instance();
	~Lenn(void);

	void init();
	void levelUp();

	int getResource() { return stamina; }
	int getMaxResource() { return staminaMax; }
	int getXpToLevel(){ return xpToLevel; }
	BattleCommand* getCommand(int index){ return commands[index]; };
	ItemStats* getItemStatsForSlot(int whatSlot);
	Item* getItem(int slot);
	void addXP(int amount);
	void adjustResource(int amount);
};

