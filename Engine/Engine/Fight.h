#pragma once
#include "battlecommand.h"

class Fight :
	public BattleCommand
{
	std::vector<Drawable> enemyList;

	// old
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

