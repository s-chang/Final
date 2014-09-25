#include "GameStateManager.h"


GameStateManager::GameStateManager(void)
{
}


GameStateManager::~GameStateManager(void)
{
}

void GameStateManager::init()
{
	while(!states.empty())
		states.pop();
	states.push(StartMenu::instance());
	states.top()->init();

	//init all states (battle will init on state change)
	Options::instance()->init();
	NewGame::instance()->init();
	Town::instance()->init();
}
void GameStateManager::shutdown()
{
	while(!states.empty())
		states.pop();
}

void GameStateManager::update()
{
	
	int stateChange = states.top()->update();
	switch(stateChange)
	{
	case STARTMENU: // reinitialize
		init();
		break;
	case OPTIONS: // push options onto stack
		states.push(Options::instance());
		break;
	case NEWGAME: // empty stack and start new game
		states.pop();
		states.push(NewGame::instance());
		break;
	case TOWN: // empty stack and start town
		states.pop();
		states.push(Town::instance());
		break;
	case INN: // push inn onto stack
		break;
	case SHOP: // push inn onto stack
		break;
	case TAVERN: // push inn onto stack
		break;
	case TOWER: // push inn onto stack
		break;
	case BATTLE: // push inn onto stack
		break;
	case STATUSMENU: // push status window onto stack
		break;
	case RETURN: // pop once to return to previous state
		states.pop();
		break;
	default:
		break;
	}

}
void GameStateManager::render()
{
	states.top()->render();
}