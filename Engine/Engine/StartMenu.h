#pragma once
#include "gamestate.h"
#include <vector>
class StartMenu :
	public GameState
{
private:

public:
	StartMenu(void);
	~StartMenu(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

