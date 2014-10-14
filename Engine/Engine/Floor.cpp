#include "Floor.h"

#include "Roomtype.h"

Floor::Floor()
{
	stairs.setHandle("stairs");
	stairs.set3D(true);
	stairs.setHasTexture(true);
	stairs.setScale(0.5f, 0.5f, 0.5f);
	
}

Floor::~Floor()
{}

Floor *Floor::instance()
{
	static Floor floor;
	return &floor;
}


void Floor::createFloor(int floorNum)
{
	//clear out containers
	rooms.clear();
	cors.clear();
	tempRC.clear();
	chest.clear();

	//generate map
	FloorGenerator::instance()->generateMap(floorNum);

	//create temporary containers to store data
	std::vector<Room> tempRoom = FloorGenerator::instance()->getRoom();
	std::vector<Corridor> tempCor = FloorGenerator::instance()->getCorridor();



	for(unsigned int i = 0; i < tempRoom.size(); i++)
	{
		FloorRoom *theRoom; 
		std::string name;

		switch(tempRoom[i].getIcon())
		{
		case roomoneU:	{	theRoom = CorridorFactory::instance()->getRoom("room1U"); name = "room1U";	break;	}
		case roomoneD:  {	theRoom = CorridorFactory::instance()->getRoom("room1D"); name = "room1D";	break;	}
		case roomoneL:	{	theRoom = CorridorFactory::instance()->getRoom("room1L"); name = "room1L";	break;	}
		case roomoneR:  {	theRoom = CorridorFactory::instance()->getRoom("room1R"); name = "room1R";	break;	}
		case roomtwoH:	{	theRoom = CorridorFactory::instance()->getRoom("room2H"); name = "room2H";	break;	}
		case roomtwoV:	{	theRoom = CorridorFactory::instance()->getRoom("room2V"); name = "room2V";	break;	}
		case roomtwoUR:	{	theRoom = CorridorFactory::instance()->getRoom("room2UR"); name = "room2UR";	break;	}
		case roomtwoDR:	{	theRoom = CorridorFactory::instance()->getRoom("room2DR"); name = "room2DR";	break;	}
		case roomtwoDL:	{	theRoom = CorridorFactory::instance()->getRoom("room2DL"); name = "room2DL";	break;	}
		case roomtwoUL: {	theRoom = CorridorFactory::instance()->getRoom("room2UL"); name = "room2UL";	break;	}
		case roomthreeU:{	theRoom = CorridorFactory::instance()->getRoom("room3U"); name = "room3U";	break;	}
		case roomthreeD:{	theRoom = CorridorFactory::instance()->getRoom("room3D"); name = "room3D";	break;	}
		case roomthreeL:{	theRoom = CorridorFactory::instance()->getRoom("room3L"); name = "room3L";	break;	}
		case roomthreeR:{	theRoom = CorridorFactory::instance()->getRoom("room3R"); name = "room3R";	break;	}
		case roomfour:	{	theRoom = CorridorFactory::instance()->getRoom("room4"); name = "room4";		break;	}
		default:
			theRoom = CorridorFactory::instance()->getRoom("room1U"); break;
		}				
	
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

		if(rooms[i]->getStairs())
		{
			stairs.setTranslate(rooms[i]->getX() *PIXELS, 0.0f, rooms[i]->getY() *PIXELS);
		}
		Drawable temp;
		temp.setHandle("chest");
		temp.set3D(true);
		temp.setHasTexture(true);
		temp.setScale(0.5f, 0.5f, 0.5f);
		//temp.setRotate(0.0f, 180.0f, 0.0f);

		if(rooms[i]->getTreasure())
		{
			temp.setTranslate(rooms[i]->getX() *PIXELS, 0.0f, rooms[i]->getY() *PIXELS);
			chest.push_back(temp);
		}

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
			if(tempRC[i]->getName() == "room1U" || tempRC[i]->getName() == "cor1U")
			{
				if(leaveRoom1U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					//determine next room and set to On
					determineOn( tempRC[i], tempDirection);
				}
				break;
			}

			if(tempRC[i]->getName() == "room1D" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveRoom1D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}

			if(tempRC[i]->getName() == "room1R" || tempRC[i]->getName() == "cor1R")
			{
				if(leaveRoom1R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}

			if(tempRC[i]->getName() == "room1L" || tempRC[i]->getName() == "cor1L")
			{
				if(leaveRoom1L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room2V" || tempRC[i]->getName() == "cor2V")
			{
				if(leaveRoom2V(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room2H" || tempRC[i]->getName() == "cor2H")
			{
				if(leaveRoom2H(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room2UR" || tempRC[i]->getName() == "cor2UR")
			{
				if(leaveRoom2UR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room2DR" || tempRC[i]->getName() == "cor2DR")
			{
				if(leaveRoom2DR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
				break;
			}
			if(tempRC[i]->getName() == "room2UL" || tempRC[i]->getName() == "cor2UL")
			{
				if(leaveRoom2UL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room2DL" || tempRC[i]->getName() == "cor2DL")
			{
				if(leaveRoom2DL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room3U" || tempRC[i]->getName() == "cor3U")
			{
				if(leaveRoom3U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
					break;
			}
			if(tempRC[i]->getName() == "room3R" || tempRC[i]->getName() == "cor3R")
			{
				if(leaveRoom3R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}
				break;
			}
			if(tempRC[i]->getName() == "room3D" || tempRC[i]->getName() == "cor3D")
			{
				if(leaveRoom3D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "room3L" || tempRC[i]->getName() == "cor3L")
			{
				if(leaveRoom3L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "room4" || tempRC[i]->getName() == "cor4")
			{
				if(leaveRoom4(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn(tempRC[i], tempDirection);
				}	break;
			}

			/*if(tempRC[i]->getName() == "cor1U" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor1U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor1D" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor1D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor1R" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor1R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor1L" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor1L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor2V" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2V(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}

			if(tempRC[i]->getName() == "cor2H" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2H(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}

			if(tempRC[i]->getName() == "cor2UR" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2UR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor2DR" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2DR(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor2UL" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2UL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor2DL" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor2DL(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor3U" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor3U(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor3D" || tempRC[i]->getName() == "cor1D")
			{
				if(leaveCor3D(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor3R" )
			{
				if(leaveCor3R(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor3L")
			{
				if(leaveCor3L(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}
			if(tempRC[i]->getName() == "cor4")
			{
				if(leaveCor4(tempRC[i], playerX, playerZ, tempDirection))
				{
					tempRC[i]->setOn(false);
					determineOn( tempRC[i], tempDirection);
				}	break;
			}*/
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

//bool Floor::leaveCor1D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check top
//	if(playerZ > ( (roomY*PIXELS) - (CENTEROFFSET - SIDEOFFSET) ) )
//	{
//		playerZ = (roomY * PIXELS) - (CENTEROFFSET - SIDEOFFSET);
//	}
//	//check left
//	if(playerX < ((roomX*PIXELS ) - (CENTEROFFSET - SIDEOFFSET  )))
//	{
//		playerX = (roomX*PIXELS ) - (CENTEROFFSET - SIDEOFFSET  );
//	}
//	//check right
//	if(playerX > ((roomX*PIXELS) + (CENTEROFFSET - SIDEOFFSET)))
//	{
//		playerX = (roomX*PIXELS) + (CENTEROFFSET -SIDEOFFSET);
//	}
//
//	//check bottom
//	if(playerZ < ( (roomY*PIXELS) - CENTEROFFSET))
//	{
//		//check left
//		if(playerX < ((roomX*PIXELS) - (CENTEROFFSET - SIDEOFFSET)))
//			playerZ = roomY * PIXELS - CENTEROFFSET;
//		//check right
//		else if(playerX > ((roomX * PIXELS) + (CENTEROFFSET - SIDEOFFSET)))
//			playerZ = roomY * PIXELS - CENTEROFFSET;
//		else
//		{
//			direction = DOWN; return true;
//		}
//	}
//	return false;
//}
//bool Floor::leaveCor1U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check left
//	if(playerX < ((roomX*PIXELS ) - (CENTEROFFSET - SIDEOFFSET  )))
//	{
//		playerX = (roomX*PIXELS ) - (CENTEROFFSET - SIDEOFFSET  );
//	}
//	//check right
//	if(playerX > ((roomX*PIXELS) + (CENTEROFFSET - SIDEOFFSET)))
//	{
//		playerX = (roomX*PIXELS) + (CENTEROFFSET -SIDEOFFSET);
//	}
//	//check bottom
//	if(playerZ < ((roomY*PIXELS) + (CENTEROFFSET - SIDEOFFSET)))
//	{
//		playerZ = (roomY*PIXELS) + (CENTEROFFSET - SIDEOFFSET);
//	}
//
//	//check up
//	if(playerZ > ((roomY*PIXELS) + CENTEROFFSET))
//	{
//		//check left
//		if(playerX < ((roomX*PIXELS) - (CENTEROFFSET - SIDEOFFSET)))
//			playerZ = roomY*PIXELS + CENTEROFFSET;
//		//check right
//		else if(playerX > ((roomX*PIXELS) + (CENTEROFFSET - SIDEOFFSET)))
//			playerZ = roomY*PIXELS + CENTEROFFSET;
//		else
//		{
//			direction = UP; return true;
//		}
//	}
//	
//	return false;
//
//}
//bool Floor::leaveCor1L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check top
//	if(playerZ > roomY*PIXELS + ENTRANCEOFFSET)
//		playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//	//check bottom
//	if(playerZ < roomY * PIXELS - ENTRANCEOFFSET)
//		playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//	//check right
//	if(playerX > roomX * PIXELS - ENTRANCEOFFSET)
//		playerX = roomX * PIXELS - ENTRANCEOFFSET;
//	//check left
//	if(playerX < roomX* PIXELS - CENTEROFFSET)
//	{
//		direction = LEFT; return true;
//	}
//	
//
//
//	return false;
//
//}
//bool Floor::leaveCor1R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	
//	//check top
//	if(playerZ > roomY*PIXELS + ENTRANCEOFFSET)
//		playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//	//check bottom
//	if(playerZ < roomY * PIXELS - ENTRANCEOFFSET)
//		playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//	//check right
//	if(playerX > roomX * PIXELS + CENTEROFFSET)
//	{
//		direction = RIGHT; return true;
//	}		
//	//check left
//	if(playerX < roomX* PIXELS + ENTRANCEOFFSET)
//		playerX = roomX*PIXELS + ENTRANCEOFFSET;
//		
//	return false;
//}
//
//bool Floor::leaveCor2H(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//	//check top
//	if(playerZ > ((roomY*PIXELS) + ENTRANCEOFFSET))
//		playerZ = roomY*PIXELS + ENTRANCEOFFSET;
//	//check bottom
//	if(playerZ < ((roomY*PIXELS) - ENTRANCEOFFSET))
//		playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//	//check right
//	if(playerX > (roomX *PIXELS + CENTEROFFSET))
//	{
//		direction = RIGHT;
//		return true;
//	}
//	//check left
//	if(playerX < (roomX * PIXELS - CENTEROFFSET))
//	{
//		direction = LEFT;
//		return true;
//	}
//		
//		
//	return false;
//}
//
//bool Floor::leaveCor2V(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check left
//	if(playerX < (roomX*PIXELS-ENTRANCEOFFSET))
//		playerX = (float)(roomX*PIXELS - ENTRANCEOFFSET);
//	//check right
//	if(playerX > (roomX*PIXELS+ENTRANCEOFFSET))
//		playerX = (float)(roomX*PIXELS+ENTRANCEOFFSET);
//	//check down
//	if(playerZ < roomY*PIXELS-CENTEROFFSET)
//	{
//		direction = DOWN;
//		return true;
//	}
//	//check up
//	if(playerZ > roomY*PIXELS + CENTEROFFSET)
//	{
//		direction = UP;
//		return true;
//	}
//	
//
//	return false;
//}
//
//bool Floor::leaveCor3D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//top
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//		playerZ = roomY *PIXELS + ENTRANCEOFFSET;
//
//	//left
//	if(playerX < (roomX * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS - CENTEROFFSET))
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//
//	//right
//	if(playerX > (roomX * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX > (roomX * PIXELS + CENTEROFFSET))
//			{
//				direction = RIGHT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//
//	//bottom
//	if(playerZ < (roomY * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX * PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS - CENTEROFFSET))
//			{
//				direction = DOWN; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//
//	return false;
//
//}
//bool Floor::leaveCor3U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check bottom
//	if(playerZ < (roomY * PIXELS - ENTRANCEOFFSET))
//		playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//
//	//left
//	if(playerX < (roomX * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS - CENTEROFFSET))
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//
//	//right
//	if(playerX > (roomX * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX > (roomX * PIXELS + CENTEROFFSET))
//			{
//				direction = RIGHT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//
//	//top
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX*PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS + CENTEROFFSET))
//			{
//				direction = UP; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//		}
//	}
//	
//	return false;
//}
//bool Floor::leaveCor3L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check right
//	if(playerX > (roomX*PIXELS + ENTRANCEOFFSET))
//	{
//		playerX = roomX*PIXELS + ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check UP
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX*PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS + CENTEROFFSET))
//			{
//				direction = UP; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//bottom
//	if(playerZ < (roomY * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX * PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS - CENTEROFFSET))
//			{
//				direction = DOWN; return true;
//			}
//		}else
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//	}
//
//	//left
//	if(playerX < (roomX * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS - CENTEROFFSET))
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//
//	return false;
//}
//bool Floor::leaveCor3R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check left
//	if(playerX < roomX*PIXELS - ENTRANCEOFFSET)
//	{
//		playerX = roomX*PIXELS - ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check UP
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX*PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS + CENTEROFFSET))
//			{
//				direction = UP; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//bottom
//	if(playerZ < (roomY * PIXELS - ENTRANCEOFFSET))
//	{
//		if((playerX > (roomX * PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS - CENTEROFFSET))
//			{
//				direction = DOWN; return true;
//			}
//		}else
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//	}
//
//	//right
//	if(playerX > (roomX * PIXELS + ENTRANCEOFFSET))
//	{
//		if((playerZ > (roomY * PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX > (roomX * PIXELS + CENTEROFFSET))
//			{
//				direction = RIGHT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET;		
//			return false;
//		}
//	}
//	return false;
//}
//
//bool Floor::leaveCor2UR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//	//check left
//	if(playerX < (roomX*PIXELS - ENTRANCEOFFSET))
//	{
//		playerX = roomX*PIXELS - ENTRANCEOFFSET;
//		return false;
//	}
//	//check bottom
//	if(playerZ < (roomY*PIXELS - ENTRANCEOFFSET))
//	{
//		playerZ = roomY*PIXELS - ENTRANCEOFFSET;
//		return false;
//	}
//	//check top
//	if( (playerZ >  (roomX*PIXELS + ENTRANCEOFFSET)) )
//	{
//		//check right
//		if((playerX > (roomX * PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX * PIXELS + ENTRANCEOFFSET) ))
//		{
//			if(playerZ > (roomX * PIXELS + CENTEROFFSET))
//			{
//				direction = UP; return true;
//			}
//			
//		}else
//		{
//			playerZ = roomX *PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//		
//	}
//	//check right
//	if(playerX > roomX*PIXELS + ENTRANCEOFFSET)
//	{
//		//check top
//		if(playerZ < roomY*PIXELS + ENTRANCEOFFSET)			
//		{
//			//check the far right
//			if((playerX > (roomX * PIXELS + CENTEROFFSET)) && (playerX < (roomX * PIXELS - CENTEROFFSET)))
//			{
//				direction = RIGHT; return true;
//			}
//		}else if(playerZ > roomY*PIXELS + ENTRANCEOFFSET)
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	return false;
//}
//bool Floor::leaveCor2DR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check top
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//		playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//	//check left
//	if(playerX < (roomX * PIXELS - ENTRANCEOFFSET))
//		playerX = roomX * PIXELS - ENTRANCEOFFSET;
//
//	//check down
//	if(playerZ < (roomY * PIXELS - ENTRANCEOFFSET))
//	{
//		//check right
//		if(playerX < roomX * PIXELS + ENTRANCEOFFSET)
//		{
//			if(playerZ < (roomY * PIXELS - CENTEROFFSET))
//			{
//				direction = DOWN; return true;
//			}
//		}else if(playerX > roomX * PIXELS + ENTRANCEOFFSET)
//		{
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check right
//	if(playerX > (roomX * PIXELS + ENTRANCEOFFSET))
//	{
//		//check down
//		if(playerZ > roomY * PIXELS - ENTRANCEOFFSET)
//		{
//			if(playerX > (roomX * PIXELS + CENTEROFFSET))
//			{
//				direction = RIGHT; return true;
//			}
//		}else if(playerZ < roomY * PIXELS - ENTRANCEOFFSET)
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET; 
//			return false;
//		}
//	}
//	return false;
//}
//bool Floor::leaveCor2UL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check down
//	if(playerZ < roomY*PIXELS - ENTRANCEOFFSET)
//	{
//		playerZ = roomY*PIXELS - ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check right
//	if(playerX > roomX*PIXELS + ENTRANCEOFFSET)
//	{
//		playerX = roomX*PIXELS + ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check left
//	if(playerX < (roomX * PIXELS) - ENTRANCEOFFSET)
//	{
//		if((playerZ > (roomY*PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS) - CENTEROFFSET)
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check top
//	if(playerZ > (roomY * PIXELS) + ENTRANCEOFFSET)
//	{
//		if((playerX > (roomX *PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX *PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS) + CENTEROFFSET)
//			{
//				direction = UP; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	return false;
//
//}
//bool Floor::leaveCor2DL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check right
//	if(playerX > roomX*PIXELS + ENTRANCEOFFSET)
//	{
//		playerX = roomX*PIXELS + ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check top
//	if(playerZ > (roomY * PIXELS + ENTRANCEOFFSET))
//	{
//		playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//		return false;
//	}
//
//	//check bottom
//	if(playerZ < (roomY * PIXELS) - ENTRANCEOFFSET)
//	{
//		if((playerX > (roomX *PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX *PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ < (roomY * PIXELS) - CENTEROFFSET)
//			{
//				direction = DOWN; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check left
//	if(playerX < (roomX * PIXELS) - ENTRANCEOFFSET)
//	{
//		if((playerZ > (roomY*PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS) - CENTEROFFSET)
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//
//
//
//	
//	return false;
//}
//
//bool Floor::leaveCor4(FloorCorridor* rc, float &playerX, float &playerZ, int &direction)
//{
//	float roomX = (float)rc->getX();
//	float roomY = (float)rc->getY();
//
//	//check top
//	if(playerZ > (roomY * PIXELS) + ENTRANCEOFFSET)
//	{
//		if((playerX > (roomX *PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX *PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ > (roomY * PIXELS) + CENTEROFFSET)
//			{
//				direction = UP; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check bottom
//	if(playerZ < (roomY * PIXELS) - ENTRANCEOFFSET)
//	{
//		if((playerX > (roomX *PIXELS - ENTRANCEOFFSET)) && (playerX < (roomX *PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerZ < (roomY * PIXELS) - CENTEROFFSET)
//			{
//				direction = DOWN; return true;
//			}
//		}else
//		{
//			playerZ = roomY * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check left
//	if(playerX < (roomX * PIXELS) - ENTRANCEOFFSET)
//	{
//		if((playerZ > (roomY*PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX < (roomX * PIXELS) - CENTEROFFSET)
//			{
//				direction = LEFT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS - ENTRANCEOFFSET;
//			return false;
//		}
//	}
//
//	//check right
//	if(playerX > (roomX * PIXELS) + ENTRANCEOFFSET)
//	{
//		if((playerZ > (roomY*PIXELS - ENTRANCEOFFSET)) && (playerZ < (roomY * PIXELS + ENTRANCEOFFSET)))
//		{
//			if(playerX > (roomX * PIXELS) + CENTEROFFSET)
//			{
//				direction = RIGHT; return true;
//			}
//		}else
//		{
//			playerX = roomX * PIXELS + ENTRANCEOFFSET;
//			return false;
//		}
//	}
//	
//	return false;
//}
//

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


void Floor::checkChest(float &playerX, float &playerZ)
{
	FloorRoom* temp = NULL;
	//check for on
	for(unsigned int i = 0; i < rooms.size(); i++)
	{
		if(rooms[i]->getOn())
		{
			//check for chest
			if(rooms[i]->getTreasure())
			{
				//set temp pointer
				temp = rooms[i];
			}
			break;
		}
	}

	//Check chests if temp isn't null
	if(temp)
	{
		for(unsigned int i = 0; i < chest.size(); i++)
		{
			//compare positions
			if( (temp->getX() * PIXELS == chest[i].getTranslate().x) && ((temp->getY() * PIXELS) == chest[i].getTranslate().z)
				)				
			{
				
			}
		}
	}
}


bool Floor::checkStairs(float &playerX, float &playerZ)
{
	//check for on
	for(unsigned int i = 0; i < rooms.size(); i++)
	{
		if(rooms[i]->getOn())
		{
			if(playerX < stairs.getTranslate().x + 2.0f &&
				playerX > stairs.getTranslate().x - 2.0f &&
				playerZ < stairs.getTranslate().z + 2.0f &&
				playerZ > stairs.getTranslate().z - 2.0f)
				return true;
		}
	}
	
	return false;
}

bool Floor::rangeChest(float &playerX, float &playerZ)
{
	FloorRoom *temp = NULL;
	//check for on
	for(unsigned int i = 0; i < rooms.size(); i++)
	{
		if(rooms[i]->getOn())
		{
			
			temp = rooms[i];			
		}
	}

	if(temp)
	{
		//determine the chest to check
		float x = 0.0f, y = 0.0f;

		for(unsigned int i = 0; i < chest.size(); i++)
		{
			if( ((chest[i].getTranslate().x) == (temp->getX() * PIXELS)) &&	
				((chest[i].getTranslate().z) == (temp->getY() * PIXELS)) )
			{
				x = chest[i].getTranslate().x;
				y = chest[i].getTranslate().z;
			}
		}

		//determine location of the chest
			if(playerX < x + 2.0f &&
				playerX > x - 2.0f &&
				playerZ < y + 2.0f &&
				playerZ > y - 2.0f)
				return true;
	}

	return false;
}

void Floor::removeChest(int X, int Y)
{
	std::vector<Drawable> temp;
	for(unsigned int i = 0; i < chest.size(); i++)
	{
		if(chest[i].getTranslate().x == X * PIXELS &&
			chest[i].getTranslate().z == Y * PIXELS)
		{
			//reconstruct vector without this chest
			continue;
		}
		temp.push_back(chest[i]);
	}
	chest = temp;
}

Drawable Floor::getStairs()
{
	return stairs;
}

std::vector<Drawable> Floor::getChests()
{
	return chest;
}