#include "Tower.h"
#include "Floor.h"
#include <stdlib.h>
#include "Player.h"
#include "Text.h"
#include <stdio.h>

Tower::Tower(void)
{
	player.setHandle("grem");
	player.set3D(true);
	bossLevel5 = bossLevel10 = bossLevel15 = false;
	towerstate = 0;
	enterFromTown = true;
	chestHelp = false;

	RECT tempR;
	tempR.top = 50;
	tempR.left = 700;
	floortext.setRect(tempR);

	//floor number
	textBackground.setHandle("blueBox");
	textBackground.setTranslate(725.0f, 62.5f, 0.0f);
	textBackground.setScale(0.9f,0.7f,0.0f);

	//item get
	itemGetBackground.setHandle("blueBox");
	itemGetBackground.setTranslate(200.0f, 62.5f, 0.0f);
	itemGetBackground.setScale(3.0f, 2.0f, 0.0f);

	miniTimer = 0.0f;
	

	//set player position
	playerX = player.getTranslate().x;
	playerZ = player.getTranslate().z;

	cam.init(800,600);
	//set camera lookat 
	cam.setLookAt(playerX, -3.75f, playerZ);
	cam.setEyePos(0.0f,10.0f,-20.0f);
	cam.setProj();

	loop = false;

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
	swprintf_s(confirm, 3, L"F");
}

void Tower::shutdown()
{

	Floor::instance()->shutdown();
}

int Tower::update()
{
	Engine::Input* input = Engine::Input::instance();

	const int ENTER = 0, MOVE = 1, FIGHT = 2, DEATH = 3, EXIT = 4;

	const float speed = 15.0f * Engine::Timer::instance()->getDT();
	static int slowcount = 0;
	const int limiter =  25;
	//stepCounter = limiter;

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


			//change text for current floor

			swprintf_s(tempText, 20, L"Floor %d", currentFloor); 
			floortext.setText(tempText);

			towerstate = MOVE;
			break;
		}
	case MOVE:
		{
			if(loop)
				miniTimer -= Engine::Timer::instance()->getDT();
			
			if(miniTimer < 0.0f)
			{
				loop = false;
				miniTimer = 0.0f;
			}

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
				++slowcount;
				if(slowcount == limiter)
				{
					slowcount = 0;
					--stepCounter;
				}
			}


			Floor::instance()->checkCollision(playerX, playerZ);

			//check for collision with chest
			Floor::instance()->checkChest(playerX, playerZ);

			if(Floor::instance()->rangeChest(playerX, playerZ))
			{
				chestHelp = true;
				//check for On and set to temp variable
				FloorRoom* temp = NULL;

				for(unsigned int i = 0; i < Floor::instance()->getRooms().size(); i++)
				{
					if(Floor::instance()->getRooms()[i]->getOn())
						temp = Floor::instance()->getRooms()[i];
				}

			
				if(input->check_mouse_button(LEFT_MOUSE_BUTTON))
				{
					if(!input->check_button_down(DIK_F))
					{
						input->set_button(DIK_F,true);
						
						//check if the room has a chest
						if(temp->getTreasure())
						{
							//set chest to false
							temp->setTreasure(false);
							Floor::instance()->removeChest(temp->getX(), temp->getY());
							loop = true;
							miniTimer = 3.0f;
							getItem();	
							
						}
					}
				}else
				{
					input->set_button(DIK_F, false);
					chestHelp = false;
				}

			}

			//check for collision with stairs
			if(Floor::instance()->checkStairs(playerX, playerZ))
			{
				++currentFloor;
				towerstate = ENTER;
				stepCounter = rand() % 5 + 15;

				if(currentFloor > 5)
				{
					Player::instance()->fifthComplete();
				}

				if(currentFloor > 10)
				{
					Player::instance()->tenthComplete();
				}

				if(currentFloor > 15)
				{
					currentFloor = 1;
					towerstate = ENTER;
					stepCounter = rand() % 5 + 15;
					return TOWN;
				}
				break;

			}


			//if the stepCounter is true, set battle to true, switch to battle state
			if(stepCounter == 0)
			{
				towerstate = FIGHT;
			}


			player.setTranslate(playerX, 0.0f, playerZ);
			cam.setLookAt(player.getTranslate().x, 5.0f, player.getTranslate().z);
			cam.setEyePos(player.getTranslate().x, cam.getEyePos().y, player.getTranslate().z - 20.0f);
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
			//restore player health
			Player::instance()->restoreCharacters();
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

	if(SUCCEEDED(directX->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
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
			graphics->render(Floor::instance()->getStairs(), &cam);

			//draw treasure chests
			for(unsigned int i = 0; i < Floor::instance()->getChests().size(); i++)
			{
				graphics->render(Floor::instance()->getChests()[i], &cam);
			}

			//draw player
			graphics->render(player, &cam);

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{				
				graphics->render(textBackground, &cam);

				if(loop)
				{
				//draw background for confirm
					graphics->render(itemGetBackground, &cam);
				}

			
				Engine::DX::instance()->getSprite()->End();
				//render floor text
				Engine::Text::instance()->render(floortext);
				
				//render item get text
				if(loop)
				{
					Engine::Text::instance()->render((long)(itemGetBackground.getTranslate().y-12.5f), (long)(itemGetBackground.getTranslate().x-100), ItemText, D3DCOLOR_ARGB(255,255,255,255));
				}
							
			}

		}
		directX->getDevice()->EndScene();
	}
	directX->getDevice()->Present(0,0,0,0);

}

void Tower::getItem()
{

	//add a random item to player inventory, and set display message
	switch(currentFloor)
	{
	case 1: case 2: case 3: case 4: 
		{
			getLowItem();

			break;
		}
	case 6: case 7: case 8: case 9: case 11: case 12:
		{
			getMidItem();
			break;
		}
	 case 13: case 14:
		{
			getHighItem();
			break;
		}
	default:
		break;								

	}
}

void Tower::getLowItem()
{
	int temp = rand() % 25;
	switch(temp)
	{
	case 0 : 
		{
			swprintf_s(ItemText, 128, L"You received Clothes.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Clothes"));
			break;
		}

	case 1: 
		{
			swprintf_s(ItemText, 128, L"You received Leather Armor.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Leather Armor"));
			break;
		}
	case 2: 
		{
			swprintf_s(ItemText, 128, L"You received Splintered Staff.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Splintered Staff"));
			break;
		}
	case 3: 
		{
			swprintf_s(ItemText, 128, L"You received Rod.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Rod"));
			break;
		}
	case 4: 
		{
			swprintf_s(ItemText, 128, L"You received Weathered Spear.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Weathered Spear"));
			break;
		}
	case 5:
		{
			swprintf_s(ItemText, 128, L"You received Short Spear.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Short Spear"));
			break;
		}
	case 6:
		{
			swprintf_s(ItemText, 128, L"You received Chipped Dagger.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Chipped Dagger"));
			break;
		}
	case 7:
		{
			swprintf_s(ItemText, 128, L"You received Knife.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Knife"));
			break;
		}
	case 8: case 9: case 10: case 11:
		{
			swprintf_s(ItemText, 128, L"You received Potion.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Potion"));
			break;
		}
	case 12: case 13: case 14: case 15:
		{
			swprintf_s(ItemText, 128, L"You received Ether.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Ether"));
			break;
		}
	case 16: case 17: case 18: case 19:
		{
			swprintf_s(ItemText, 128, L"You received Revive.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Revive"));
			break;
		}
	default:
		{
			int gold = rand() % 50 + 50;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}
}

void Tower::getMidItem()
{
	int temp = rand() % 25;
	switch(temp)
	{
	case 0 : 
		{
			swprintf_s(ItemText, 128, L"You received Chain Mail.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Chain Mail"));
			break;
		}

	case 1: 
		{
			swprintf_s(ItemText, 128, L"You received Enchanted Robe.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Enchanted Robe"));
			break;
		}
	case 2: 
		{
			swprintf_s(ItemText, 128, L"You received Staff.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Staff"));
			break;
		}
	case 3: 
		{
			swprintf_s(ItemText, 128, L"You received Rod of Light.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Rod of Light"));
			break;
		}
	case 4: 
		{
			swprintf_s(ItemText, 128, L"You received Harpoon.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Harpoon"));
			break;
		}
	case 5:
		{
			swprintf_s(ItemText, 128, L"You received Spear.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Spear"));
			break;
		}
	case 6:
		{
			swprintf_s(ItemText, 128, L"You received Sting.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Sting"));
			break;
		}
	case 7:
		{
			swprintf_s(ItemText, 128, L"You received Needle.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Needle"));
			break;
		}
	case 8: case 9: case 10: case 11:
		{
			swprintf_s(ItemText, 128, L"You received Potion.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Potion"));
			break;
		}
	case 12: case 13: case 14: case 15:
		{
			swprintf_s(ItemText, 128, L"You received Ether.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Ether"));
			break;
		}
	case 16: case 17: case 18: case 19:
		{
			swprintf_s(ItemText, 128, L"You received Revive.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Revive"));
			break;
		}
	default:
		{
			int gold = rand() % 100 + 100;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}
}

void Tower::getHighItem()
{
	int temp = rand() % 25;
	switch(temp)
	{
	case 0 : 
		{
			swprintf_s(ItemText, 128, L"You received Plate Armor.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Plate Armor"));
			break;
		}

	case 1: 
		{
			swprintf_s(ItemText, 128, L"You received Dragon Armor.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Dragon Armor"));
			break;
		}
	case 2: 
		{
			swprintf_s(ItemText, 128, L"You received Staff of Wisdom.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Staff of Wisdom"));
			break;
		}
	case 3: 
		{
			swprintf_s(ItemText, 128, L"You received Iron Staff.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Iron Staff"));
			break;
		}
	case 4: 
		{
			swprintf_s(ItemText, 128, L"You received Lance.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Lance"));
			break;
		}
	case 5:
		{
			swprintf_s(ItemText, 128, L"You received Gae Bolg.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Gae Bolg"));
			break;
		}
	case 6:
		{
			swprintf_s(ItemText, 128, L"You received Dagger.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Dagger"));
			break;
		}
	case 7:
		{
			swprintf_s(ItemText, 128, L"You received Night's Bane.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Night's Bane"));
			break;
		}
	case 8: case 9: case 10: case 11:
		{
			swprintf_s(ItemText, 128, L"You received Potion.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Potion"));
			break;
		}
	case 12: case 13: case 14: case 15:
		{
			swprintf_s(ItemText, 128, L"You received Ether.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Ether"));
			break;
		}
	case 16: case 17: case 18: case 19:
		{
			swprintf_s(ItemText, 128, L"You received Revive.");
			Player::instance()->addItem(ItemFactory::instance()->getItem("Revive"));
			break;
		}
	default:
		{
			int gold = rand() % 200 + 200;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}
}