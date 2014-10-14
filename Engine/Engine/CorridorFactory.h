#pragma once

#include "FloorRoom.h"
#include <string>

class CorridorFactory
{
private:

	CorridorFactory();

public:
	static CorridorFactory* instance();
	~CorridorFactory();

	FloorCorridor *getCor(std::string handle);
	FloorRoom *getRoom(std::string handle);
};