#pragma once
#include "gamestate.h"
class SkillsMenu :
	public GameState
{
private:
	Drawable background;
	Drawable cmdWindow;
	std::vector<Drawable> buttons;
	SkillsMenu(void);
public:
	static SkillsMenu* instance();
	~SkillsMenu(void);

	void init();
	void shutdown();

	int update();
	void render();
};