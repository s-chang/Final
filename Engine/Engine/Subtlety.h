#pragma once
#include "battlecommand.h"
class Subtlety :
	public BattleCommand
{
private:
	std::vector<BattleCommand*> skillList;
	bool selection;
public:
	Subtlety(void);
	~Subtlety(void);
	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};
