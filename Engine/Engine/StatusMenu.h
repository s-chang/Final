#pragma once
#include "GameState.h"
#include "Drawable.h"
#include <vector>

enum Status_states{
	STAT_MAIN,
	ITEM,
	EQUIP,
	SKILLS,
	STATUS,
	STAT_OPTIONS,
	BACK
};

#define MAX_CHARACTERS 3


class StatusMenu : public GameState
{
private:
	int status_state;
	Drawable background;
	std::vector<Drawable> portraits;
	std::vector<Drawable> names;
	std::vector<Drawable> hp_resource;
	std::vector<Drawable> status_commands;
	std::vector<Drawable> gold_playtime;
	std::vector<GameState> status_menu_selections;

	void setMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world, Drawable &object);
	void resetMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world);

	StatusMenu();
public:
	~StatusMenu();
	static StatusMenu *instance();

	virtual void init();
	virtual void shutdown();

	virtual int update();
	virtual void render();

};