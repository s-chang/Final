#include "Floor.h"

#include "Roomtype.h"

Floor::Floor()
{}

Floor::~Floor()
{}

Floor *Floor::instance()
{
	static Floor floor;
	return &floor;
}


void Floor::createFloor(int floorNum)
{
	//generate map
	FloorGenerator::instance()->generateMap(floorNum);

	//create temporary containers to store data
	std::vector<Room> tempRoom = FloorGenerator::instance()->getRoom();
	std::vector<Corridor> tempCor = FloorGenerator::instance()->getCorridor();



	for(unsigned int i = 0; i < tempRoom.size(); i++)
	{
		FloorRoom *theRoom = new FloorRoom();
		std::string name;

		switch(tempRoom[i].getIcon())
		{
		case roomoneU:	{	name = "room1U";	break;	}
		case roomoneD:  {	name = "room1D";	break;	}
		case roomoneL:	{	name = "room1L";	break;	}
		case roomoneR:  {	name = "room1R";	break;	}
		case roomtwoH:	{	name = "room2H";	break;	}
		case roomtwoV:	{	name = "room2V";	break;	}
		case roomtwoUR:	{	name = "room2UR";	break;	}
		case roomtwoDR:	{	name = "room2DR";	break;	}
		case roomtwoDL:	{	name = "room2DL";	break;	}
		case roomtwoUL: {	name = "room2UL";	break;	}
		case roomthreeU:{	name = "room3U";	break;	}
		case roomthreeD:{	name = "room3D";	break;	}
		case roomthreeL:{	name = "room3L";	break;	}
		case roomthreeR:{	name = "room3R";	break;	}
		case roomfour:	{	name = "room4";		break;	}
		}				

		theRoom->init("room");
		theRoom->setArrival(tempRoom[i].getArrival());
		if(tempRoom[i].getArrival())
		{
			theRoom->setOn(true);
		}
		theRoom->setTreasure(tempRoom[i].getTreasure());
		theRoom->setStairs(tempRoom[i].getStairs());
		theRoom->setTranslate(D3DXVECTOR3((float)tempRoom[i].getY() * PIXELS, 0.0f, -(float)tempRoom[i].getX() * PIXELS));
		theRoom->setName(name);
		theRoom->setX(tempRoom[i].getY());
		theRoom->setY(-tempRoom[i].getX());

		rooms.push_back(theRoom);
	}



	for(unsigned int i = 0; i < tempCor.size(); i++)
	{
		FloorCorridor *cor;

		std::string name;

		switch(tempCor[i].getIcon())
		{
		case oneU:	{	cor = CorridorFactory::instance()->getCor("cor1U");	 name = "cor1U"; break;		}
		case oneD:	{	cor = CorridorFactory::instance()->getCor("cor1D");	 name = "cor1D"; break;		}
		case oneL:	{	cor = CorridorFactory::instance()->getCor("cor1L");	 name = "cor1L"; break;		}
		case oneR:	{	cor = CorridorFactory::instance()->getCor("cor1R");	 name = "cor1R"; break;		}
		case twoH:	{	cor = CorridorFactory::instance()->getCor("cor2H");	 name = "cor2H"; break;		}
		case twoV:	{	cor = CorridorFactory::instance()->getCor("cor2V");	 name = "cor2V"; break;		}
		case twoUR:	{	cor = CorridorFactory::instance()->getCor("cor2UR"); name = "cor2UR"; break;		}
		case twoDR:	{	cor = CorridorFactory::instance()->getCor("cor2DR"); name = "cor2DR"; break;		}
		case twoDL:	{	cor = CorridorFactory::instance()->getCor("cor2DL"); name = "cor2DL"; break;		}
		case twoUL:	{	cor = CorridorFactory::instance()->getCor("cor2UL"); name = "cor2UL"; break;		}
		case threeU:{	cor = CorridorFactory::instance()->getCor("cor3U");	 name = "cor3U"; break;		}
		case threeD:{	cor = CorridorFactory::instance()->getCor("cor3D");	 name = "cor3D"; break;		}
		case threeL:{	cor = CorridorFactory::instance()->getCor("cor3L");	 name = "cor3L"; break;		}
		case threeR:{	cor = CorridorFactory::instance()->getCor("cor3R");	 name = "cor3R"; break;		}
		case four:	{	cor = CorridorFactory::instance()->getCor("cor4");	 name = "cor4"; break;		}
		default:
			cor = new FloorCorridor(); break;
		}
		cor->setTranslate(D3DXVECTOR3((float)tempCor[i].getY() * PIXELS, 0.0f, -(float)tempCor[i].getX() * PIXELS));
		cor->setX(tempCor[i].getY());
		cor->setY(-tempCor[i].getX());
		cor->setName(name);
		cors.push_back(cor);
	}	

	for(unsigned int i = 0; i < rooms.size(); i++)
	{
		tempRC.push_back(rooms[i]);
	}

	for(unsigned int i = 0; i < cors.size(); i++)
	{
		tempRC.push_back(cors[i]);
	}

}

std::vector<FloorRoom*> Floor::getRooms()
{
	return rooms;
}

std::vector<FloorCorridor*> Floor::getCors()
{
	return cors;
}

void Floor::shutdown()
{
	FloorGenerator::instance()->shutdown();


	if(!rooms.empty())
	{
		for(unsigned int i = 0; i < rooms.size(); i++)
		{
			delete rooms[i];
		}
		rooms.clear();
	}

	if(!cors.empty())
	{
		for(unsigned int i = 0; i < cors.size(); i++)
		{
			delete cors[i];
		}
		cors.clear();
	}

	tempRC.clear();
}

void Floor::checkCollision(float &playerX, float &playerZ)
{
	
	static int tempDirection = 0;
	
	//Determine which area the player is at
	for(unsigned int i = 0; i < tempRC.size(); i++)
	{
		//check where the player is on - always starts on the arrival room
		if(tempRC[i]->getOn())
		{
			//check names for appropriate collision
			if(tempRC[i]->getName() == "room1U")
			{
				if(leaveRoom1U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					//determine next room and set to On
					determineOn( tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "room1D")
			{
				if(leaveRoom1D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "room1R")
			{
				if(leaveRoom1R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "room1L")
			{
				if(leaveRoom1L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2V")
			{
				if(leaveRoom2V(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2H")
			{
				if(leaveRoom2H(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2UR")
			{
				if(leaveRoom2UR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2DR")
			{
				if(leaveRoom2DR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2UL")
			{
				if(leaveRoom2UL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room2DL")
			{
				if(leaveRoom2DL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room3U")
			{
				if(leaveRoom3U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room3R")
			{
				if(leaveRoom3R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room3D")
			{
				if(leaveRoom3D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room3L")
			{
				if(leaveRoom3L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "room4")
			{
				if(leaveRoom4(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "cor1U")
			{
				if(leaveCor1U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor1D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor1R")
			{
				if(leaveCor1R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor1L")
			{
				if(leaveCor1L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor2V")
			{
				if(leaveCor2V(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "cor2H")
			{
				if(leaveCor2H(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}

			if(tempRC[i]->getName() == "cor2UR")
			{
				if(leaveCor2UR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor2DR")
			{
				if(leaveCor2DR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor2UL")
			{
				if(leaveCor2UL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor2DL")
			{
				if(leaveCor2DL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor3U")
			{
				if(leaveCor3U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor3D")
			{
				if(leaveCor3D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor3R")
			{
				if(leaveCor3R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor3L")
			{
				if(leaveCor3L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
			if(tempRC[i]->getName() == "cor4")
			{
				if(leaveCor4(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}
			}
		}
	}
}

bool Floor::leaveRoom1U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET); }

	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);  }

	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET)) { playerZ = (float)(roomY * PIXELS - CENTEROFFSET);  }
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	return false;
}
bool Floor::leaveRoom1D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET);	}

	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);	}

	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET)) { playerZ = (float)(roomY * PIXELS + CENTEROFFSET);   }
	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	return false;
}
bool Floor::leaveRoom1L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check Right
	if(playerX > ((roomX*PIXELS)+CENTEROFFSET)){ playerX = (float)(roomX*PIXELS + CENTEROFFSET);}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
	return false;

}
bool Floor::leaveRoom1R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check Left
	if(playerX < ((roomX*PIXELS)-CENTEROFFSET)){ playerX = (float)(roomX*PIXELS - CENTEROFFSET);}
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	return false;
}

bool Floor::leaveRoom2H(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	return false;
}
bool Floor::leaveRoom2V(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET);	}
	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);	}
	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}

	return false;
}

bool Floor::leaveRoom2UR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();


	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET);	}
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	return false;
}
bool Floor::leaveRoom2DR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET);	}
	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	

	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	return false;
}
bool Floor::leaveRoom2UL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);	}
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	

	return false;
}
bool Floor::leaveRoom2DL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);	}
	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
		//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	return false;
}

bool Floor::leaveRoom3D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check Top
	if(playerZ > ((roomY*PIXELS)+CENTEROFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
		//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	return false;
}
bool Floor::leaveRoom3U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check Bottom
	if(playerZ < ((roomY*PIXELS) -CENTEROFFSET)){ playerZ = (float)(roomY*PIXELS-CENTEROFFSET); }
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	return false;
}
bool Floor::leaveRoom3L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET)) { playerX = (float)((roomX*PIXELS) + CENTEROFFSET);	}
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}

	return false;
}
bool Floor::leaveRoom3R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET)) { playerX = (float)(( roomX*PIXELS) - CENTEROFFSET);	}
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}

	return false;
}

bool Floor::leaveRoom4(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();
	//check Left
	if(playerX < ((roomX*PIXELS) - CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS - CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS - CENTEROFFSET; }
		else { direction = LEFT; return true;}		
	}	
	//check Right
	if(playerX > ((roomX*PIXELS) + CENTEROFFSET))
	{
		//if the player is above the door
		if(playerZ > ((roomY*PIXELS)+ ENTRANCEOFFSET)){playerX = roomX * PIXELS + CENTEROFFSET;}
		//if the player is below the door
		else if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET)){playerX = roomX*PIXELS + CENTEROFFSET; }
		else { direction = RIGHT; return true;}		
	}	
	//check top
	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET);  } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) { playerZ = (float)(roomY*PIXELS + CENTEROFFSET); }
		else { direction = UP; return true;	}
	}
	//check bottom
	if(playerZ < ((roomY*PIXELS) - CENTEROFFSET))
	{
		//if the player is to the left of the door
		if(playerX < (roomX*PIXELS) - ENTRANCEOFFSET) { playerZ = (float)(roomY*PIXELS - CENTEROFFSET);   } 
		//if the player is to the right of the door
		else if(playerX > (roomX*PIXELS + ENTRANCEOFFSET)) {	playerZ = (float)(roomY*PIXELS - CENTEROFFSET); }
		else {	direction = DOWN; return true;	}
	}
	return false;
}

bool Floor::leaveCor1D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor1U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor1L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor1R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}

bool Floor::leaveCor2H(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}


bool Floor::leaveCor2V(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{
	float roomX = (float)rc->getX();
	float roomY = (float)rc->getY();

	//check left
	if(playerX < (roomX*PIXELS-ENTRANCEOFFSET))
		playerX = (float)(roomX*PIXELS - ENTRANCEOFFSET);
	//check right
	if(playerX > (roomX*PIXELS+ENTRANCEOFFSET))
		playerX = (float)(roomX*PIXELS+ENTRANCEOFFSET);
	//check down
	if(playerZ < roomY*PIXELS-CENTEROFFSET)
	{
		direction = DOWN;
		return true;
	}
	//check up
	if(playerZ > roomY*PIXELS + CENTEROFFSET)
	{
		direction = UP;
		return true;
	}
	

	return false;
}

bool Floor::leaveCor3D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor3U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor3L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor3R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}

bool Floor::leaveCor2UR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor2DR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor2UL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}
bool Floor::leaveCor2DL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}

bool Floor::leaveCor4(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
{return false;}


void Floor::determineOn( FloorCorridor* previous, int direction)
{
	//determine previous location
	int x = previous->getX();
	int y = previous->getY();

	switch(direction)
	{
	case UP: ++y; break;
	case DOWN: --y; break;
	case LEFT: --x; break;
	case RIGHT: ++x; break;	
	}

	for(unsigned int i = 0; i < tempRC.size(); i++)
	{
		if((tempRC[i]->getX() == x) && (tempRC[i]->getY() == y))
			tempRC[i]->setOn(true);
	}
}

