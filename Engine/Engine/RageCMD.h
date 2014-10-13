#pragma once
#include "battlecommand.h"
class RageCMD :
	public BattleCommand
{
private:
	std::vector<BattleCommand*> skillList;
	bool selection;
public:
	RageCMD(void);
	~RageCMD(void);
	void init();
	void update();
	void render();
	void text();
	std::string helpText();
};

