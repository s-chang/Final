#pragma once
#include "Room.h"
#include <vector>
#include <queue>
#include "RoomType.h"

#define LIMIT 5

class FloorGenerator
{
private:

	unsigned char ** map;
	int room_num;
	int room_max;
	bool add_room;

	std::vector<Corridor> corridor;
	std::vector<Room> rooms;
	std::queue<Corridor> start;	

	//checks the position if available
	void checkAvailableU(int posX, int posY, bool room);
	void checkAvailableD(int posX, int posY, bool room);
	void checkAvailableR(int posX, int posY, bool room);
	void checkAvailableL(int posX, int posY, bool room);

	//check for blank
	bool checkUp(int posX, int posY);
	bool checkDown(int posX, int posY);
	bool checkLeft(int posX, int posY);
	bool checkRight(int posX, int posY);

	//don't check for blank
	bool checkUp2(int posX, int posY);
	bool checkDown2(int posX, int posY);
	bool checkLeft2(int posX, int posY);
	bool checkRight2(int posX, int posY);

	//assigns a room or corridor to the position
	void assignUp(bool room);
	void assignDown(bool room);
	void assignLeft(bool room);
	void assignRight(bool room);
	
	void pushCor(int x, int y, unsigned char icon, bool type);
	void pushRoom(int x, int y, unsigned char icon, bool type);

	//determine whether to add a room or a corridor
	void addRC(int floornum);

	//validates the map
	bool checkValidMap();

	FloorGenerator();
	void resetMap();
	
	void emptyQueue();
	void emptyRoom();
	void emptyCor();

public:

	static FloorGenerator *instance();
	FloorGenerator(const FloorGenerator &floor);
	~FloorGenerator();
	
	void generateMap(int floornum);	

	std::vector<Corridor> getCorridor();
	std::vector<Room> getRoom();

	void shutdown();	
};