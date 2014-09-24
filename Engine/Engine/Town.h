#pragma once
#include "GameState.h"
class Town :
	public GameState
{
private:

	Town(void);
public:
	static Town* instance();
	~Town(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

