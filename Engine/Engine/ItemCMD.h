#pragma once
#include "battlecommand.h"
class ItemCMD :
	public BattleCommand
{
public:
	ItemCMD(void);
	~ItemCMD(void);

	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};
