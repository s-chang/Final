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
		LOSE = 2, WIN = 3,
		// Counters
		PLAYER_COUNT = 3;
	int ENEMY_COUNT,
		COUNTER;
};
struct TURN_STATUS
{
	//turn status: start, openwindow, selection, end;
	static const int
		START = 0, OPEN_WINDOW = 1, SELECTION = 2, END = 3;
};

class Battle :
	public GameState
{
private:
	Camera cam;

	Drawable platform;
	Drawable bWindow;
	//Drawable player;

	std::vector<Slime> enemies;
	int whosTurn, turnStatus;
	Turn turnOrder;
	//std::vector<Entity*> entityList;

	void updatePlayerTurn(Entity*);
	void updateEnemyTurn();
	
	void renderPlayerTurn(Entity*);
	void renderEnemyTurn();

	void BattleOver();

	Battle(void);
public:
	static Battle* instance();
	~Battle(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};




