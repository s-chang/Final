#pragma once
#include "battlecommand.h"
class Elemental :
	public BattleCommand
{
private:
	std::vector<BattleCommand*> skillList;
	bool selection;
public:
	Elemental(void);
	~Elemental(void);
	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};

