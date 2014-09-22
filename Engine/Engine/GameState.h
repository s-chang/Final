#pragma once

class GameState
{
private:
public:
	GameState(void){};
	~GameState(void){};

	virtual void init() = 0;
	virtual void shutdown() = 0;

	/**
	Name:		update
	Parameters: none
	Return:		int
	Description: Updates gamestate and returns the state to switch to 
	or 0 for no state change;
	*/
	virtual int update() = 0; 
	virtual void render() = 0;
};

