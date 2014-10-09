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

	//init all states (Tower/battle will init on state change)
	Options::instance()->init();
	NewGame::instance()->init();
	Town::instance()->init();
	Inn::instance()->init();
	Shop::instance()->init();
	Tavern::instance()->init();
	StatMenuManager::instance()->init();

	//init characters
	Grem::instance()->init();
	Lenn::instance()->init();
	Laz::instance()->init();

	

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
		states.push(Inn::instance());
		break;
	case SHOP: // push Shop onto stack
		states.push(Shop::instance());
		break;
	case TAVERN: // push Tavern onto stack
		states.push(Tavern::instance());
		break;
	case TOWER: // push Tower onto stack
		states.push(Tower::instance());
		states.top()->init();
		break;
	case BATTLE: // push battle onto stack
		states.push(Battle::instance());
		states.top()->init();
		break;
	case STATUSMENU: // push status window onto stack
		states.push(StatMenuManager::instance());
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