#pragma once
#include "skill.h"
class Earth :
	public Skill
{
protected:
	std::vector<Drawable> enemyList;
	float timer;
public:
	Earth(void);
	~Earth(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();
};