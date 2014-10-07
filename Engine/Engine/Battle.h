#pragma once
#include "gamestate.h"
#include "Entities.h"
#include <vector>

struct Turn{
	//whosturn
	static const int 
		PLAYER_TURN = 0,
		ENEMY_TURN = 1,
		// battleOver?
		LOSE = 2, WIN = 3, ESCAPE = 4,
		// Counters
		PLAYER_COUNT = 3;
	int ENEMY_COUNT,
		COUNTER;
};
struct TURN_STATUS
{
	//turn status: start, openwindow, selection, end;
	static const int
		START = 0, CMD = 1, END = 2;
};

class Battle :
	public GameState
{
private:
	Camera cam;

	Drawable platform;
	Drawable bWindow;
	int returnable;

	void updatePlayerTurn(Entity*);
	void updateEnemyTurn();
	
	void renderPlayerTurn(Entity*);
	void renderEnemyTurn();

	void renderNamesHelthResource();

	void BattleOver();

	Battle(void);

public:
	int whosTurn, turnStatus;
	Turn turnOrder;
	std::vector<Slime> enemies;
	std::vector<Entity*> all;
	BattleCommand* activeCMD;
	bool renderNames;
	int dmg;
	int randAI;
	bool escape;

	static Battle* instance();
	~Battle(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};




