#pragma once

#include "FloorCorridor.h"

class FloorRoom: public FloorCorridor
{
private:
	bool treasure;
	bool arrival;
	bool stairs;
	
	
public:
	FloorRoom();
	~FloorRoom();

	virtual void init(std::string handle);

	void setTreasure(bool arg);
	void setArrival(bool arg);
	void setStairs(bool arg);
	
	bool getTreasure();
	bool getArrival();
	bool getStairs();
	

		
};