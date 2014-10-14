#pragma once
#include "CorridorFactory.h"
#include "FloorGenerator.h"
#include <string>
#include <vector>

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

const float PIXELS = 30.0f;
const float CENTEROFFSET = 15.0f;
const float ENTRANCEOFFSET = 5.0f;
const float SIDEOFFSET = 10.0f;

class Floor 
{
private:
	std::vector<FloorRoom*> rooms;
	std::vector<FloorCorridor*> cors;
	std::vector<FloorCorridor*> tempRC;
	Floor();

	void determineOn( FloorCorridor *previous, int direction);

	bool leaveRoom1U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom1D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom1L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom1R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	bool leaveRoom2H(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom2V(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	bool leaveRoom2UR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom2DR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom2UL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom2DL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	bool leaveRoom3D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom3U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom3L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	bool leaveRoom3R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	bool leaveRoom4(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	//bool leaveCor1D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor1U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor1L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor1R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	//bool leaveCor2H(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor2V(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	//bool leaveCor3D(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor3U(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor3L(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor3R(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	//bool leaveCor2UR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor2DR(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor2UL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	//bool leaveCor2DL(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);

	//bool leaveCor4(FloorCorridor* rc, float &playerX, float &playerZ, int &direction);
	
	Drawable stairs;
	std::vector<Drawable> chest;

public:
	~Floor();
	static Floor *instance();
	
	void createFloor(int floorNum);
	std::vector<FloorRoom*> getRooms();
	std::vector<FloorCorridor*> getCors();


	void checkCollision(float &playerX, float &playerZ);
	void checkChest(float &playerX, float &playerZ);
	bool rangeChest(float &playerX, float &playerZ);
	bool checkStairs(float &playerX, float &playerZ);

	void removeChest(int X, int Y);

	Drawable getStairs();
	std::vector<Drawable> getChests();

	void shutdown();
};