#pragma once
#include "skill.h"
class Wind :
	public Skill
{
protected:
	std::vector<Drawable> allyList;
	float timer;
public:
	Wind(void);
	~Wind(void);

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void text();
	virtual std::string helpText();
};