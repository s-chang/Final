#include "Game.h"
#include "EngineHeaders.h"
#include "ItemFactory.h"

Game::Game()
{
}

Game::~Game()
{}

void Game::init()
{
	

	Engine::Graphics::instance()->init();
	Engine::Sound::instance()->init();
	Engine::Text::instance()->init();
	ItemFactory::instance()->loadFactory();

	gsm.init();
}

void Game::update(MSG &msg)
{
	Engine::Sound::instance()->update();
	Engine::Input::instance()->update();
	Engine::Cursor::instance()->update(Engine::Input::instance()->get_mouseX(),Engine::Input::instance()->get_mouseY());

	this->msg = msg;

	gsm.update();
}

void Game::render()
{
	gsm.render();
}

void Game::shutdown()
{
	gsm.shutdown();
	Engine::Text::instance()->shutdown();
	Engine::Sound::instance()->shutdown();
	Engine::Graphics::instance()->shutdown();
	Engine::Input::instance()->shutdown();
}

void Game::reset()
{}

