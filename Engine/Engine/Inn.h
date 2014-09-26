#pragma once
#include "gamestate.h"

#define INN_BUTTONS 1

class Inn :
	public GameState
{
private:
	Drawable bg,
			 box;
	Drawable buttons[INN_BUTTONS];
	Inn(void);
public:
	static Inn* instance();
	~Inn(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

