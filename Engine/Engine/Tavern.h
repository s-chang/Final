#pragma once
#include "gamestate.h"

#define TAVERN_BUTTONS 1

class Tavern :
	public GameState
{
private:
	Drawable bg,
			 box;
	Drawable buttons[TAVERN_BUTTONS];

	Tavern(void);
public:
	static Tavern* instance();
	~Tavern(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};
