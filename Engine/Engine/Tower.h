#pragma once
#include "gamestate.h"
#include "town.h"
class Tower :
	public GameState
{
private:
	int currentFloor;

	Tower(void);
public:
	static Tower* instance();
	~Tower(void);

	void init();
	void shutdown();

	int update(); 
	void render();

	int getFloor() { return currentFloor; };
};