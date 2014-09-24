#include "Cursor.h"


Engine::Cursor::Cursor(void)
{
	handle = "cursor";
	cursorPos.x = 300;
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

void Engine::Cursor::update(float x, float y)
{
	cursorPos.x += x;
	cursorPos.y += y;

	if(cursorPos.x < 0) cursorPos.x = 0;
	if(cursorPos.y < 0) cursorPos.y = 0;
	if(cursorPos.x > 800) cursorPos.x = 800;
	if(cursorPos.y > 600) cursorPos.y = 600;
}