#include "Game.h"
#include "EngineHeaders.h"

Game::Game()
{
}

Game::~Game()
{}

void Game::init()
{
	floor.init();
	cam = floor.getCamera();

	Engine::Graphics::instance()->init(cam, floor.getLight());
	Engine::Sound::instance()->init();
	Engine::Text::instance()->init();
	gsm.init();
}

void Game::update(MSG &msg)
{
	Engine::Sound::instance()->update();
	Engine::RawInput::instance()->getMSG(msg);
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

