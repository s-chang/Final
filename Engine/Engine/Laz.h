#pragma once
#include "entity.h"
#include "CommandList.h"
#include "Staff.h"
#include <vector>
class Laz :
	public Entity
{
private:
	int mana, manaMax;
	int xpToLevel;

	Staff* weapon;
	Armor* armor;
	Accessory* acc1,
			 * acc2;
	Rune* rune1,
		* rune2;

	BattleCommand* commands[4];

	Laz(void);
public:
	std::vector<BattleCommand*> availableCommands;
	std::vector<BattleCommand*> skills;

	static Laz* instance();
	~Laz(void);

	void init();
	void levelUp();

	int getResource() { return mana; }
	int getMaxResource() { return manaMax; }
	int getXpToLevel(){ return xpToLevel; }
	BattleCommand* getCommand(int index){ return commands[index]; };
	ItemStats* getItemStatsForSlot(int whatSlot);
	Item* getItem(int slot);
	void addXP(int amount);
	void adjustResource(int amount);
	void getSkills(std::vector<BattleCommand*>& skillList, int type);
};

