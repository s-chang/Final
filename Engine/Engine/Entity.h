#pragma once
#include "Drawable.h"

struct Stats
{		
	int xp, level, health, maxHealth;
	int attack, magic, defense, resist, speed;	
	
};

class Entity
{
protected:
	std::string name;
	Drawable mesh;
	Stats stats;
	
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
};

