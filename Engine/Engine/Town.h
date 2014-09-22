#pragma once
#include "GameState.h"
class Town :
	public GameState
{
public:
	Town(void);
	~Town(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

