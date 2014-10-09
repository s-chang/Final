#pragma once
#include "Drawable.h"
#include "Item.h"
#include "Accessory.h"
#include "Armor.h"
#include "Rune.h"
#include "ItemFactory.h"
#include "BattleCommand.h"

struct Stats
{		
	int xp, level, health, maxHealth;
	int attack, magic, defense, resist, speed;	
	
};
struct SLOT{
	static const int 
		WEAPON = 0,
		ARMOR = 1,
		ACC1 = 2,
		ACC2 = 3,
		RUNE1 = 4,
		RUNE2 = 5;
};

class Entity
{
protected:
	std::string name;
	Drawable mesh;
	Stats stats;
	bool alive;
	bool npc;
	
public:
	Entity(void);
	~Entity(void);

	virtual void init() = 0;
	virtual void levelUp() = 0;

	void setLevel(int num);
	void adjustHealth(int amount);
	Drawable * getMesh();
	Stats* getStats();
	std::string getName();

	bool isAlive();
	bool isNPC();
	bool operator()(Entity* l, Entity* r);

	// character specific
	virtual void addXP(int amount){};
	virtual void adjustResource(int amount){};
	virtual int getResource(){ return 0; };
	virtual int getMaxResource(){ return 0; };
	virtual BattleCommand* getCommand(int index){ return 0; };
	virtual ItemStats* getItemStatsForSlot(int whatSlot){ return 0; };
	virtual int getXpToLevel(){ return 0; };
	//virtual void printList(int type);
};

