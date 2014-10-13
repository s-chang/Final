#pragma once
#include "skill.h"


class Jump :
	public Skill
{
protected:
	int target;
	std::vector<Drawable> enemyList;
public:
	Jump(void);
	~Jump(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();
};

