#pragma once

#include "FloorCorridor.h"

class FloorRoom: public FloorCorridor
{
private:
	bool treasure;
	bool arrival;
	bool stairs;
	std::string name;
public:
	FloorRoom();
	~FloorRoom();

	virtual void init(std::string handle);

	void setTreasure(bool arg);
	void setArrival(bool arg);
	void setStairs(bool arg);
	void setName(std::string name);

	bool getTreasure();
	bool getArrival();
	bool getStairs();
	std::string getName();
		
};