#pragma once
#include "CorridorFactory.h"
#include <string>
#include <vector>

class Floor 
{
private:
	std::vector<FloorRoom*> rooms;
	std::vector<FloorCorridor*> cors;
		
	Floor();
public:
	~Floor();
	static Floor *instance();
	
	void createFloor(int floorNum);
	std::vector<FloorRoom*> getRooms();
	std::vector<FloorCorridor*> getCors();

	void shutdown();
};