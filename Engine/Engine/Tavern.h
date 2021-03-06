#pragma once
#include "gamestate.h"

struct TAVERN_STATE
{
	static const int 
		OPEN = 0,
		RUMORS = 1,
		TUTORIALS = 2,
		DISPLAY = 3;
};

class Tavern :
	public GameState
{
private:
	int state;
	bool help;
	bool rewarded;

	Drawable bg;
	Drawable openWindow;
	Drawable secondWindow;

	std::vector<Drawable> buttons;

	void reward();
	Tavern(void);
public:
	static Tavern* instance();
	~Tavern(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};
