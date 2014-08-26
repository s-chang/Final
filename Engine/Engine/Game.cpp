#include "Game.h"
#include "EngineHeaders.h"

Game::Game()
{
	game_state = TOWERFLOOR;
	
}

Game::~Game()
{}

void Game::init()
{


	//mesh1.init();
	//mesh1.setScale(1.0f, 1.0f, 1.0f);
	//mesh1.setHandle("grem");
	//mesh1.set3D(true);
	//mesh1.setHasTexture(false);

	floor.init();
	cam = floor.getCamera();
	//cam = &tempCam;
	//cam->init(800,600);
	//cam->setProj();
	
	Engine::Graphics::instance()->init(cam, floor.getLight());
	Engine::Sound::instance()->init();
	Engine::Text::instance()->init();
}

void Game::update(MSG &msg)
{

	Engine::Sound::instance()->update();
	Engine::RawInput::instance()->getMSG(msg);
	Engine::Input::instance()->update();
	
	this->msg = msg;
	
	
	switch(game_state)
	{
	case TITLE:
		break;
	case TOWERFLOOR:
		{
			cam = floor.getCamera();
			/*float y = mesh1.getRotate().y + Engine::Timer::instance()->getDT() * 5.0f;
			if( y > 360)
				y = 0;
			mesh1.setRotate(mesh1.getRotate().x, y, mesh1.getRotate().z);

			if(Engine::Input::instance()->push_button(DIK_W))
			{
				mesh1.setTranslate(mesh1.getTranslate().x , mesh1.getTranslate().y, mesh1.getTranslate().z + 1.0f);
			}

			if(Engine::Input::instance()->push_button(DIK_S))
			{
				mesh1.setTranslate(mesh1.getTranslate().x, mesh1.getTranslate().y, mesh1.getTranslate().z - 1.0f);
			}

			drawQ.push(mesh1);*/
			floor.update();
			drawQ = floor.getDrawQ();
			break;
		}
	}	
}

void Game::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{
			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				
				
				while(!drawQ->empty())
				{
					Engine::Graphics::instance()->render(drawQ->front(), cam);
					drawQ->pop();
				}
				
				Engine::DX::instance()->getSprite()->End();

				/*while(!textQ.empty())
				{
					Engine::Text::instance()->render(textQ.front().top, textQ.front().left, textQ.front().wordbuffer, textQ.front().color);
					textQ.pop();

				}*/
				Engine::Text::instance()->render(0,0);
			}
		}
		Engine::DX::instance()->getDevice()->EndScene();


	}
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}

void Game::shutdown()
{
	Engine::Text::instance()->shutdown();
	Engine::Sound::instance()->shutdown();
	Engine::Graphics::instance()->shutdown();
	Engine::Input::instance()->shutdown();
}

void Game::reset()
{}

