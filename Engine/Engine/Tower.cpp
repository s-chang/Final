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
	exitNow = false;
	itemName = "Nothing";
	convertItemName = L"Nothing";

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

	RECT r;
	r.left = 100;
	r.top = 30;
	exitText.setText(L"Do you want to exit?");
	exitText.setRect(r);
	
	r.left = 170;
	r.right = 260;
	r.top = 60;
	r.bottom = 90;
	exitYes.setText(L"Yes");
	exitYes.setTranslate(215.0f, 85.0f, 0.0f);
	exitYes.setRect(r);

	r.top = 90;
	r.bottom = 120;
	exitNo.setText(L"No");
	exitNo.setTranslate(215.0f, 115.0f, 0.0f);
	exitNo.setRect(r);

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
			if(exitNow)
			{
				if( exitYes.checkOn(Engine::Cursor::instance()->cursorPos.x, Engine::Cursor::instance()->cursorPos.y, 3))
				{
					exitYes.setColor(D3DCOLOR_ARGB(255,255,255,0));
					if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON))
					{
						exitNow = false;
						towerstate = EXIT;
					}
				}else
				{
					exitYes.setColor(D3DCOLOR_ARGB(255,255,255,255));
				}

				if(exitNo.checkOn(Engine::Cursor::instance()->cursorPos.x, Engine::Cursor::instance()->cursorPos.y, 3))
				{
					exitNo.setColor(D3DCOLOR_ARGB(255,255,255,0));
					if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON))
					{
						exitNow = false;						
					}
				}else
				{
					exitNo.setColor(D3DCOLOR_ARGB(255,255,255,255));
				}

				break;
			}else
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


					if(input->push_button(DIK_F))
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

				//check for collision with exit
				if(Floor::instance()->checkExit(playerX, playerZ) )
				{
					if( input->push_button(DIK_F))
					{
						if(!input->check_button_down(DIK_F))
						{
							input->set_button(DIK_F, true);
							exitNow = true;
							break;
						}
					}else
							input->set_button(DIK_F, false);
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
			Player::instance()->restoreCharacters();
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

			//Draw exit
			graphics->render(Floor::instance()->getExit(), &cam);

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

				if(loop || exitNow)
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

				if(exitNow)
				{
					Engine::Text::instance()->render(exitText);
					Engine::Text::instance()->render(exitYes);
					Engine::Text::instance()->render(exitNo);
				}

			}
			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK))){
				Engine::Graphics::instance()->drawCursor();
				Engine::DX::instance()->getSprite()->End();
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
	bool gold = false;
	switch(temp)
	{
	case 0: {	itemName = "Clothes";			break;	}
	case 1: {	itemName = "Leather Armor";		break;	}
	case 2: {	itemName = "Splintered Staff";  break;  }
	case 3: {	itemName = "Rod";				break;  }
	case 4: {	itemName = "Weathered Spear";	break;  }
	case 5: {	itemName = "Short Spear";		break;  }
	case 6: {	itemName = "Chipped Dagger";    break;  }
	case 7: {	itemName = "Knife";				break;  }
	case 8: case 9: case 10: case 11:
		{	itemName = "Potion";			break;  } 		
	case 12: case 13: case 14: case 15:
		{	itemName = "Ether";				break;	}			
	case 16: case 17: case 18: case 19:
		{	itemName = "Revive";			break;  }
	default:
		{
			gold = true;
			int gold = rand() % 50 + 50;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}

	if(!gold)
	{
		convertItemName = std::wstring(itemName.begin(), itemName.end());
		swprintf_s(ItemText, 128, L"You received %s.", convertItemName.c_str());
		Player::instance()->addItem(ItemFactory::instance()->getItem(itemName));
	}

}

void Tower::getMidItem()
{
	int temp = rand() % 25;
	bool gold = false;
	switch(temp)
	{
	case 0: {	itemName = "Chain Mail";			break;	}
	case 1: {	itemName = "Enchanted Robe";		break;	}
	case 2: {	itemName = "Staff";					break;  }
	case 3: {	itemName = "Rod of Light";			break;  }
	case 4: {	itemName = "Harpoon";				break;  }
	case 5: {	itemName = "Spear";					break;  }
	case 6: {	itemName = "Sting";					break;  }
	case 7: {	itemName = "Needle";				break;  }
	case 8: case 9: case 10: case 11:
		{	itemName = "Potion";				break;  } 		
	case 12: case 13: case 14: case 15:
		{	itemName = "Ether";					break;	}			
	case 16: case 17: case 18: case 19:
		{	itemName = "Revive";				break;  }
	default:
		{
			gold = true;
			int gold = rand() % 100 + 100;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}

	if(!gold)
	{
		convertItemName = std::wstring(itemName.begin(), itemName.end());
		swprintf_s(ItemText, 128, L"You received %s.", convertItemName.c_str());
		Player::instance()->addItem(ItemFactory::instance()->getItem(itemName));
	}
}

void Tower::getHighItem()
{
	int temp = rand() % 25;
	bool gold = false;
	switch(temp)
	{
	case 0: {	itemName = "Plate Armor";			break;	}
	case 1: {	itemName = "Dragon Armor";			break;	}
	case 2: {	itemName = "Staff of Wisdom";		break;  }
	case 3: {	itemName = "Iron Staff";			break;  }
	case 4: {	itemName = "Lance";					break;  }
	case 5: {	itemName = "Gae Bolg";				break;  }
	case 6: {	itemName = "Dagger";				break;  }
	case 7: {	itemName = "Night's Bane";			break;  }
	case 8: case 9: case 10: case 11:
		{	itemName = "Potion";				break;  } 		
	case 12: case 13: case 14: case 15:
		{	itemName = "Ether";					break;	}			
	case 16: case 17: case 18: case 19:
		{	itemName = "Revive";				break;  }
	default:
		{
			gold = true;
			int gold = rand() % 200 + 200;
			swprintf_s(ItemText, 128, L"You received %d gold.", gold);
			Player::instance()->adjustGold(gold);
			break;
		}
	}

	if(!gold)
	{
		convertItemName = std::wstring(itemName.begin(), itemName.end());
		swprintf_s(ItemText, 128, L"You received %s.", convertItemName.c_str());
		Player::instance()->addItem(ItemFactory::instance()->getItem(itemName));
	}
}