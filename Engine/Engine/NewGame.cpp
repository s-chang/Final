#include "NewGame.h"


NewGame::NewGame(void)
{
}

NewGame* NewGame::instance()
{
	static NewGame ng;
	return &ng;
}

NewGame::~NewGame(void)
{
}

void NewGame::init()
{
}

void NewGame::shutdown()
{
}

int NewGame::update()
{
	// TODO: opening cutscene
	return TOWN;
}

void NewGame::render()
{
}