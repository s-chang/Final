#pragma once
#include "gamestates.h"
#include <stack>

enum GameStates
{
	STARTMENU = 1, OPTIONS, NEWGAME,
	TOWN, INN, SHOP, TAVERN,
	TOWER, BATTLE, STATUSMENU, RETURN,
};

class GameStateManager
{
private:
	std::stack<GameState*> states;
public:
	GameStateManager(void);
	~GameStateManager(void);

	void init();
	void shutdown();

	void update();
	void render();

};

