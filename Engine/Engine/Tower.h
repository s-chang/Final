#pragma once
#include "gamestate.h"
#include "town.h"
#include "Drawable.h"
#include "Camera.h"

class Tower :
	public GameState
{
private:
	int currentFloor;
	float playerX, playerZ;

	bool enterFromTown;
	int towerstate;

	Drawable player;
	Drawable floortext;
	Drawable textBackground;
	wchar_t tempText[20];

	Camera cam;

	unsigned int stepCounter;

	bool bossLevel5;
	bool bossLevel10;
	bool bossLevel15;

	Tower(void);
public:
	static Tower* instance();
	~Tower(void);

	virtual void init();
	virtual void shutdown();

	virtual int update(); 
	virtual void render();

	int getFloor() { return currentFloor; };
};