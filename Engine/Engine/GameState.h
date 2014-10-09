#pragma once
#include "EngineHeaders.h"
enum GameStates
{
	STARTMENU = 1, 
	OPTIONS, NEWGAME, CONTINUE,
	TOWN, INN, SHOP, TAVERN,
	TOWER, BATTLE, STATUSMENU, RETURN,
};

class GameState
{
private:
public:
	GameState(void){};
	~GameState(void){};

	virtual void init() = 0;
	virtual void shutdown() = 0;

	/**
	Name:		update
	Parameters: none
	Return:		int
	Description: Updates gamestate and returns the state to switch to 
	or 0 for no state change;
	*/
	virtual int update() = 0; 
	virtual void render() = 0;
};

struct STATUS_STATE{
	static const int 
		MAIN = 1,
		INVENTORY = 2,
		EQUIP = 3,
		SKILLS = 4,
		STATUS = 5,
		OPTIONS = 6;
};