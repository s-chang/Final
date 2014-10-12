#pragma once
#include "BattleCommand.h"

struct SKILL_TYPES
{
	static const int 
		RAGE = 0,
		SUBTLETY = 1,
		ELIMINATE = 2,
		ELEMENTAL = 3,
		DARK = 4,
		NONE = 99;
};

class Skill:
	public BattleCommand
{
protected:
	int type;
public:
	Skill(void);
	~Skill(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();

	int getType();
};

