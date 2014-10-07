#include "BattleCommand.h"


BattleCommand::BattleCommand(void)
{
	name = "NONE";
	on = false;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = 0;
	rect.right = 0;
}


BattleCommand::~BattleCommand(void)
{
}

void BattleCommand::init()
{
}

void BattleCommand::update()
{
}

void BattleCommand::render()
{
}

void BattleCommand::text()
{
}

std::string BattleCommand::helpText()
{
	return "Nothing to do...";
}

std::string BattleCommand::getName()
{
	return name;
}
RECT BattleCommand::getRect(){
	return rect;
}

void BattleCommand::setRect(int top,int left)
{
	rect.top = top;
	rect.left = left;
	rect.bottom = top+40;
	rect.right = left+100;
}

void BattleCommand::checkOn()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	if(c->cursorPos.x > rect.left+15 && c->cursorPos.x < rect.right &&
		c->cursorPos.y > rect.top+15 && c->cursorPos.y < rect.bottom)
		on = true;
	else 
		on = false;
}

bool BattleCommand::isOn()
{
	return on;
}