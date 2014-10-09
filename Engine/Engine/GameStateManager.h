#pragma once
#include "gamestates.h"
#include "Player.h"
#include <stack>



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

