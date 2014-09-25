#pragma once
#include "GameState.h"
class Town :
	public GameState
{
private:
	// bound on z at 7.7 bounds on x -40 to 49
	Drawable player;
	Drawable town;
	Drawable helpBar,
			 mBox;

	Camera cam;
	Light light;

	Town(void);
public:
	static Town* instance();
	~Town(void);

	void init();
	void shutdown();

	int update(); 
	void render();
};

