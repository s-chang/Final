#pragma once

#include <queue>
#include "Camera.h"
#include "Floor.h"
#include "GameStateManager.h"

enum{
TITLE,
TOWERFLOOR,
};


class Game
{
private:
	//int game_state;
	Floor floor;
	void reset();
	Camera *cam;

	MSG msg;
	
	GameStateManager gsm;

public:
	Game();
	~Game();

	void init();

	void update(MSG &msg);
	void render();

	void shutdown();
};