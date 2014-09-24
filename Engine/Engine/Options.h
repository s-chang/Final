#pragma once
#include "gamestate.h"
#define OPBUTTONS 8

class Options :
	public GameState
{
private:
	Drawable bg, box,
			 buttons[OPBUTTONS];

	Options(void);
public:
	static Options* instance();
	~Options(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

