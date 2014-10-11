#include "Fight.h"
#include "Battle.h"

Fight::Fight(void) : BattleCommand()
{
	name = "Fight";
}


Fight::~Fight(void)
{
}

void Fight::init()
{
	enemyList.clear();
	int num_enemies = Battle::instance()->turnOrder.ENEMY_COUNT;
	Drawable tempCommands;
	RECT tempR;
	SCDATA scdata = { 70.0f, 445.0f, 420, 20, 460, 170, L"Slime"};

	for(int i = 0; i < num_enemies; i++){
		tempCommands.setTranslate(scdata.x,scdata.y+=30,0.0f);
		tempR.left = scdata.l;
		tempR.right = scdata.r;
		tempR.top = scdata.t+=30;
		tempR.bottom = scdata.b+=30;
		tempCommands.init();
		tempCommands.setText(scdata.name);
		tempCommands.setRect(tempR);
		enemyList.push_back(tempCommands);
	}
}

void Fight::update()
{
	help = "Select an enemy by clicking its name or right click to return";
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();
	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->turnStatus = TURN_STATUS::START;
		help = "Use basic attack on an enemy";
		return;
	}
	
	for(unsigned int i = 0; i < enemyList.size(); i++){
		if(enemyList[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						if(b->enemies[i].isAlive()){
							// if the enemy highlighted is alive then do dmg calculations
							Entity* player = b->all[b->turnOrder.COUNTER];
							Entity* enemy = &b->enemies[i];
							int atk = player->getStats()->attack + player->getItemStatsForSlot(SLOT::WEAPON)->atk;
							int def = enemy->getStats()->defense;
							int dmg = atk - def;
							if(dmg < 0)
								dmg = 0;
							enemy->adjustHealth(-dmg);

							b->dmg = dmg;
							b->turnStatus = TURN_STATUS::END;

							help = "Use basic attack on an enemy";
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
}

void Fight::render()
{
}

void Fight::text()
{
	for(unsigned int i = 0; i < enemyList.size(); i++){
		if(Battle::instance()->enemies[i].isAlive())
			Engine::Text::instance()->render(enemyList[i].getRect().top, 
				enemyList[i].getRect().left, enemyList[i].getPlainText(), enemyList[i].getColor());
	}
}

std::string Fight::helpText()
{
	return help;
}
