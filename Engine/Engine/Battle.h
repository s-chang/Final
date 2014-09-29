#pragma once
#include "gamestate.h"
#include "Entities.h"
#include <vector>

class Battle :
	public GameState
{
private:
	Camera cam;

	Drawable platform;
	Drawable bWindow;

	Drawable player;

	Battle(void);
public:
	static Battle* instance();
	~Battle(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};


