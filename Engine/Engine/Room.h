#pragma once
#include "Corridor.h"

class Room : public Corridor
{
private:
	bool treasure;
	bool arrival;
	bool stairs;
public:
	Room();
	~Room();

	void setRoom(Corridor room, bool treasure, bool stairs);

	virtual void init();

	void setTreasure(bool arg);
	void setStairs(bool arg);
	void setArrival(bool arg);

	bool getTreasure();
	bool getStairs();
	bool getArrival();

};