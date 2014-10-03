#pragma once
#include <string>

struct SKILL_TYPES
{
	
	static const int 
		RAGE = 0,
		SUBTLETY = 1,
		ELIMINATE = 2,
		ELEMENTAL = 3,
		DARK = 4;
};

class Skill
{
protected:
	std::string name;
	int type;
public:
	Skill(void);
	~Skill(void);
};

