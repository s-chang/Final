#pragma once
#include <string>
#include <Windows.h>
#include "EngineHeaders.h"
//#include "Battle.h"

// command list Fight, item, run, rage, cover, subtlety, eliminate, elemental, dark, spirit
class BattleCommand
{
protected:
	std::string name,
		help;
	bool on;
	// for placement in 2d space and for checking hovering
	RECT rect;
public:
	BattleCommand(void);
	~BattleCommand(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();

	std::string getName();
	void setRect(int top, int left);
	RECT getRect();
	void checkOn();
	bool isOn();
};

