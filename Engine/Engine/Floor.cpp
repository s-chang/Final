#include "Floor.h"
#include "FloorGenerator.h"
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
		theRoom->setTreasure(tempRoom[i].getTreasure());
		theRoom->setStairs(tempRoom[i].getStairs());
		theRoom->setTranslate(D3DXVECTOR3((float)tempRoom[i].getY() * 30.0f, 0.0f, (float)tempRoom[i].getX() * 30.0f));
		theRoom->setName(name);

		rooms.push_back(theRoom);
	}

	

	for(unsigned int i = 0; i < tempCor.size(); i++)
	{
		FloorCorridor *cor;

		switch(tempCor[i].getIcon())
		{
		case oneU:	{	cor = CorridorFactory::instance()->getCor("cor1U");	break;		}
		case oneD:	{	cor = CorridorFactory::instance()->getCor("cor1D");	break;		}
		case oneL:	{	cor = CorridorFactory::instance()->getCor("cor1L");	break;		}
		case oneR:	{	cor = CorridorFactory::instance()->getCor("cor1R");	break;		}
		case twoH:	{	cor = CorridorFactory::instance()->getCor("cor2H");	break;		}
		case twoV:	{	cor = CorridorFactory::instance()->getCor("cor2V");	break;		}
		case twoUR:	{	cor = CorridorFactory::instance()->getCor("cor2UR");	break;		}
		case twoDR:	{	cor = CorridorFactory::instance()->getCor("cor2DR");	break;		}
		case twoDL:	{	cor = CorridorFactory::instance()->getCor("cor2DL");	break;		}
		case twoUL:	{	cor = CorridorFactory::instance()->getCor("cor2UL");	break;		}
		case threeU:{	cor = CorridorFactory::instance()->getCor("cor3U");	break;		}
		case threeD:{	cor = CorridorFactory::instance()->getCor("cor3D");	break;		}
		case threeL:{	cor = CorridorFactory::instance()->getCor("cor3L");	break;		}
		case threeR:{	cor = CorridorFactory::instance()->getCor("cor3R");	break;		}
		case four:	{	cor = CorridorFactory::instance()->getCor("cor4");	break;		}
		default:
			cor = new FloorCorridor(); break;
		}
		cor->setTranslate(D3DXVECTOR3((float)tempCor[i].getY() * 30.0f, 0.0f, (float)tempCor[i].getX() * 30.0f));
		cors.push_back(cor);
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
}
