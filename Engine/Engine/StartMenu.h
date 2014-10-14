#pragma once
#include "gamestate.h"
#include "Drawable.h"
#include <vector>

#define MENU_BUTTON_CNT 4

class StartMenu :
	public GameState
{
private:
	Drawable bg, logo,
			 buttons[MENU_BUTTON_CNT];
	
	bool drawLogo;
	float logoCounter;

	StartMenu(void);
public:
	static StartMenu* instance();
	~StartMenu(void);
	
	void init();
	void shutdown();

	int update(); 
	void render();
};

