#pragma once
#include "Entities.h"

#define INVENTORY_CAP 39

class Player
{
private:
	Grem* grem;
	Lenn* lenn;
	Laz* laz;

	std::vector<Entity*> team;
	std::vector<Item*> inventory;
	int gold;
	bool completedFifth;
	bool completedTenth;

	Player(void);
public:
	static Player* instance();
	~Player(void);

	void init();
	void shutdown();

	void addItem(Item*);
	void removeItem(Item);
	std::vector<Item*>* getInventory();
	void getItemsOfType(std::vector<Item*>& itemList, std::string type);

	void adjustGold(int amount);
	int getGold();

	void fifthComplete();
	bool hasCompletedFifth();

	void tenthComplete();
	bool hasCompletedtenth();

	bool checkDeath();
	void restoreCharacters();
};

