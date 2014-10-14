#pragma once
#include "skill.h"
class Steal :
	public Skill
{
protected:
	std::vector<Drawable> enemyList;
	bool stole;
	float timer;
	void getItem();
public:
	Steal(void);
	~Steal(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();
};