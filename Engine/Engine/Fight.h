#pragma once
#include "battlecommand.h"

class Fight :
	public BattleCommand
{
	int enemyHighlight;
	int top,left;
	RECT r2;
public:
	Fight(void);
	~Fight(void);

	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};

