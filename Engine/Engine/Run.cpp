#include "Run.h"
#include "Battle.h"

Run::Run(void): BattleCommand()
{
	name = "Run";
	help = "Run away from battle";
}


Run::~Run(void)
{
}


void Run::init()
{
}

void Run::update()
{
	//if(rand()%100 > 20)
		Battle::instance()->escape = true;
	//else
		//Battle::instance()->turnStatus = TURN_STATUS::END;
}

void Run::render()
{

}

void Run::text()
{

}

std::string Run::helpText()
{
	return help;
}
