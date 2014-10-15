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
	bool exitNow;

	std::string itemName;
	std::wstring convertItemName;
	int towerstate;

	Drawable player;
	Drawable floortext;

	Drawable exitText;
	Drawable exitYes;
	Drawable exitNo;
	
	Drawable textBackground;
	Drawable itemGetBackground;

	wchar_t tempText[20];
	wchar_t confirm[3];
	wchar_t ItemText[128];

	bool loop;
	bool chestHelp;

	Camera cam;

	unsigned int stepCounter;
	float miniTimer;

	bool bossLevel5;
	bool bossLevel10;
	bool bossLevel15;

	void getItem();
	void getLowItem();
	void getMidItem();
	void getHighItem();

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