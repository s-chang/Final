#include "Tower.h"
#include "Floor.h"
#include <stdlib.h>
#include "Player.h"


Tower::Tower(void)
{
	player.setHandle("grem");
	player.set3D(true);
	bossLevel5 = bossLevel10 = bossLevel15 = false;
	towerstate = 0;
	enterFromTown = true;
	
	//set player position
	playerX = player.getTranslate().x;
	playerZ = player.getTranslate().z;

	cam.init(800,600);
	//set camera lookat 
	cam.setLookAt(playerX, -3.75f, playerZ);
	cam.setEyePos(0.0f,10.0f,-20.0f);
	cam.setProj();

	
}


Tower::~Tower(void)
{
}

Tower* Tower::instance()
{
	static Tower tower;
	return &tower;
}

void Tower::init()
{
	stepCounter = rand() % 5 + 15;				
	
}

void Tower::shutdown()
{

	Floor::instance()->shutdown();
}

int Tower::update()
{
	Engine::Input* input = Engine::Input::instance();

	const int ENTER = 0, MOVE = 1, FIGHT = 2, DEATH = 3, EXIT = 4;

	const float speed = 0.1f;
	static int slowcount = 0;
	const int limiter =  25;

	switch(towerstate)
	{
	case ENTER:
		{
			if(enterFromTown)
			{
				currentFloor = Town::instance()->getFloor();
				Floor::instance()->createFloor(currentFloor);
				enterFromTown = false;
			}else
			{
				Floor::instance()->createFloor(currentFloor);
			}
			//set Player position according to arrival room
			for(unsigned int i = 0; i < Floor::instance()->getRooms().size(); i++)
			{
				if(Floor::instance()->getRooms()[i]->getArrival())
				{
					playerX = Floor::instance()->getRooms()[i]->getInfo().getTranslate().x;
					playerZ = Floor::instance()->getRooms()[i]->getInfo().getTranslate().z;
				}
			}

			player.setTranslate(playerX, 0.0f, playerZ);
			//set the camera
			cam.setLookAt(playerX, 0.0f, playerZ);
			cam.setEyePos(playerX, 20.0f, playerZ - 10.0f);
			cam.setProj();

			towerstate = MOVE;
			break;
		}
	case MOVE:
		{
			//check player defeat
			if(Player::instance()->checkDeath())
			{
				towerstate = DEATH;
				break;
			}

			//push the statusMenu state if G is pressed
			if(input->push_button(DIK_G))
			{
				if(!input->check_button_down(DIK_G))
				{
					input->set_button(DIK_G,true);
					return STATUSMENU;
				}
			} else input->set_button(DIK_G,false);

		
			if(input->push_button(DIK_W))
			{
				playerZ += speed;
				player.setRotate(0.0f, 180.0f, 0.0f);
				cam.setEyePos(cam.getEyePos().x, cam.getEyePos().y, cam.getEyePos().z + speed);
				++slowcount;
				if(slowcount == limiter)
					{
					slowcount = 0;
					--stepCounter;
				}
			}

			if(input->push_button(DIK_S))
			{
				playerZ -= speed;
				player.setRotate(0.0f, 0.0f, 0.0f);
				cam.setEyePos(cam.getEyePos().x, cam.getEyePos().y, cam.getEyePos().z - speed);
				++slowcount;
				if(slowcount == limiter)
					{
					slowcount = 0;
					--stepCounter;
				}
				
			}

			if(input->push_button(DIK_A))
			{
				playerX -= speed;
				player.setRotate(0.0f, 90.0f, 0.0f);
				cam.setEyePos(cam.getEyePos().x - speed, cam.getEyePos().y, cam.getEyePos().z );
				++slowcount;
				if(slowcount == limiter)
					{
					slowcount = 0;
					--stepCounter;
				}
			
			}
			if(input->push_button(DIK_D))
			{
				playerX += speed;
				player.setRotate(0.0f, 270.0f, 0.0f);
				cam.setEyePos(cam.getEyePos().x + speed, cam.getEyePos().y, cam.getEyePos().z);
				++slowcount;
				if(slowcount == limiter)
				{
					slowcount = 0;
					--stepCounter;
				}
			}

			
			//if the stepCounter is true, set battle to true, switch to battle state
			if(stepCounter == 0)
			{
				towerstate = FIGHT;
			}

			player.setTranslate(playerX, 0.0f, playerZ);
			cam.setLookAt(player.getTranslate().x, 5.0f, player.getTranslate().z);
			cam.setProj();

			break;
		}


	case FIGHT:
		{
			towerstate = MOVE;
			stepCounter = rand() % 5 + 15;
			return BATTLE;
			break;
		}
	case DEATH:
		{
			towerstate = ENTER;
			enterFromTown = true;
			stepCounter = rand() % 5 + 15;
			return TOWN;
			break;
		}
	case EXIT:
		{
			towerstate = ENTER;
			enterFromTown = true;
			stepCounter = rand() % 5 + 15;
			return TOWN;
			break;
		}
	}//end switch
	return 0;
}

void Tower::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	Engine::Graphics * graphics = Engine::Graphics::instance();
	Engine::DX* directX = Engine::DX::instance();

	if(SUCCEEDED(directX->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(directX->getDevice()->BeginScene()))
		{
			//draw corridors
			for(unsigned int i = 0; i < Floor::instance()->getCors().size(); i++)
			{
				graphics->render(Floor::instance()->getCors()[i]->getInfo(), &cam);
			}

			//draw rooms
			for(unsigned int i = 0; i < Floor::instance()->getRooms().size(); i++)
			{
				graphics->render(Floor::instance()->getRooms()[i]->getInfo(), &cam);
			}

			//Draw stairs

			//draw treasure chests

			//draw player
			graphics->render(player, &cam);
		}
		directX->getDevice()->EndScene();
	}
	directX->getDevice()->Present(0,0,0,0);

}