#pragma once
#include "gamestate.h"
class NewGame :
	public GameState
{
private:

	NewGame(void);
public:
	static NewGame* instance();
	~NewGame(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

