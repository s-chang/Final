#pragma once
#include "battlecommand.h"
class Elemental :
	public BattleCommand
{
private:
	std::vector<BattleCommand*> skillList;
public:
	Elemental(void);
	~Elemental(void);
	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};

