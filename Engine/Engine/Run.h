#pragma once
#include "battlecommand.h"
class Run :
	public BattleCommand
{
public:
	Run(void);
	~Run(void);

	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};

