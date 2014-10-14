#include "Skill.h"


Skill::Skill(void) : BattleCommand()
{
	type = SKILL_TYPES::NONE;
	cost = 0;
}


Skill::~Skill(void)
{

}

void Skill::init()
{
}
void Skill::update()
{
}
void Skill::render()
{
}
void Skill::text()
{
}
std::string Skill::helpText()
{
	return help;
}

int Skill::getType()
{
	return type;
}

int Skill::getCost()
{
	return cost;
}