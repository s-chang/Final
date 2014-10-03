#pragma once
#include <string>
#include <Windows.h>

// command list Fight, item, run, rage, cover, subtlety, eliminate, elemental, dark, spirit
class BattleCommand
{
protected:
	std::string name;
	bool on;
	RECT rect;
public:
	BattleCommand(void);
	~BattleCommand(void);

	void update();
	void render();
	void text();
	void helpText();

	std::string getName();
	bool isOn();
};

