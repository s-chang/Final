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
	bool alive;
	
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
	bool operator()(Entity* l, Entity* r);

	// character specific
	virtual int getResource(){ return 0; };
	virtual int getMaxResource(){ return 0; };
	virtual std::string getCommand(int index){ return 0; };
	//virtual void printList(int type);
};

