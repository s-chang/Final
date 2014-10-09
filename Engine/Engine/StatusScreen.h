#pragma once
#include "gamestate.h"
#include "Player.h"
class StatusScreen :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> buttons;
	std::vector<Drawable> portraits;
	int who;

	void renderStats(Entity*);
	StatusScreen(void);
public:
	static StatusScreen* instance();
	~StatusScreen(void);

	void init();
	void shutdown();

	int update();
	void render();
};