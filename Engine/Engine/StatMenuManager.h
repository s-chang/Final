#pragma once
#include "GameState.h"
#include <stack>

class StatMenuManager : public GameState
{
private:
	std::stack<GameState*> statusState;

	StatMenuManager();
public:
	~StatMenuManager();
	static StatMenuManager *instance();

	virtual void init();
	virtual void shutdown();

	virtual int update();
	virtual void render();

};