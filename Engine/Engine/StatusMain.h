#pragma once
#include "gamestate.h"
#define MAX_CHARACTERS 3

class StatusMain :
	public GameState
{
private:
	Drawable background;
	std::vector<Drawable> portraits;
	std::vector<Drawable> names;
	std::vector<Drawable> hp_resource;
	std::vector<Drawable> status_commands;
	std::vector<Drawable> gold_playtime;

	void setMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world, Drawable &object);
	void resetMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world);

	StatusMain(void);
public:
	static StatusMain* instance();
	~StatusMain(void);

	void init();
	void shutdown();

	int update();
	void render();
};

