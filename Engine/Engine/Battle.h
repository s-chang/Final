#pragma once
#include "gamestate.h"
class Battle :
	public GameState
{
private:

	Battle(void);
public:
	static Battle* instance();
	~Battle(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};


