#include "Cursor.h"


Engine::Cursor::Cursor(void)
{
	handle = "cursor";
	cursorPos.x = 400;
	cursorPos.y = 300;
}

Engine::Cursor* Engine::Cursor::instance()
{
	static Cursor input;
	return &input;
}

Engine::Cursor::~Cursor(void)
{
}

void Engine::Cursor::update(long x, long y)
{
	cursorPos.x += x;
	cursorPos.y += y;

	if(cursorPos.x < 0) cursorPos.x = 0;
	if(cursorPos.y < 0) cursorPos.y = 0;
	if(cursorPos.x > 800) cursorPos.x = 800;
	if(cursorPos.y > 600) cursorPos.y = 600;
}

std::string Engine::Cursor::getHandle()
{
	return handle;
}