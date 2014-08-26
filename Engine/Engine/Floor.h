#pragma once

#include "Drawable.h"
#include <queue>
#include <vector>
#include "Camera.h"
#include "Light.h"

#define msize 32

class Floor 
{
private:
	std::vector<Drawable> rooms;
	std::vector<Drawable> corridor;
	std::vector<Drawable> enemies;
	std::vector<Drawable> treasure;
	Drawable stair;

	Drawable player;
	
	std::queue<Drawable> drawQ;

	Camera floorCam;

	Drawable roomMain;
	Drawable roomSide1;
	Drawable roomSide2;
	Drawable roomSide3;
	Drawable roomSide4;

	Light light;

	int map[msize][msize];
	
public:
	Floor();
	~Floor();

	void loadDefaultFloor();

	void init();
	void update();
	std::queue<Drawable>* getDrawQ();
	Camera *getCamera();
	Light *getLight() {return &light;}
};