#include "Earth.h"
#include "Battle.h"

Earth::Earth(void) : Skill()
{
	name = "Earth";
	type = SKILL_TYPES::ELEMENTAL;
	help = "Crush your foes with the power of Earth. Mana Cost: 7";
	cost = 7;
	timer = 0;
}


Earth::~Earth(void)
{
}

void Earth::init()
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

	SCDATA all = { 270.0f, 505.0f, 480, 220, 520, 370, L"All"};
	tempCommands.setTranslate(all.x,all.y+=30,0.0f);
	tempR.left = all.l;
	tempR.right = all.r;
	tempR.top = all.t+=30;
	tempR.bottom = all.b+=30;
	tempCommands.init();
	tempCommands.setText(all.name);
	tempCommands.setRect(tempR);
	enemyList.push_back(tempCommands);
	
	timer = 0;
}

void Earth::update()
{
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();

	if(Laz::instance()->getResource() < cost){
		help = "Sorry insufficient Mana.";
		timer += Engine::Timer::instance()->getDT();
		if(timer > 1){
			b->activeCMD = NULL;
			b->turnStatus = TURN_STATUS::START;
			help = "Crush your foes with the power of Earth. Mana Cost: 7";
		}
		return;
	}

	help = "Select an enemy by clicking its name or right click to return";

	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->turnStatus = TURN_STATUS::START;
		help = "Crush your foes with the power of Earth. Mana Cost: 7";
		return;
	}

	for(unsigned int i = 0; i < enemyList.size(); i++){
		if(enemyList[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						if(i < Battle::instance()->enemies.size()){
							if(b->enemies[i].isAlive()){
								Entity* player = Laz::instance();
								Entity* enemy = &b->enemies[i];
								
								int mag = player->getStats()->magic + player->getItemStatsForSlot(SLOT::WEAPON)->mag;
								int res = enemy->getStats()->resist;
								int dmg = mag - res;
								if(dmg < 0)
									dmg = 0;

								enemy->adjustHealth(-dmg);
								player->adjustResource(-cost);
								b->dmg = dmg;
								b->turnStatus = TURN_STATUS::END;
								help = "Crush your foes with the power of Earth. Mana Cost: 7";
							}
						}
						else{
							//attack all
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
}


void Earth::render()
{
}

void Earth::text()
{
	for(unsigned int i = 0; i < enemyList.size(); i++){
		if(i < Battle::instance()->enemies.size()){
			if(Battle::instance()->enemies[i].isAlive())
				Engine::Text::instance()->render(enemyList[i].getRect().top, 
				enemyList[i].getRect().left, enemyList[i].getPlainText(), enemyList[i].getColor());
		}
		else {
			//Engine::Text::instance()->render(enemyList[i].getRect().top, 
				//enemyList[i].getRect().left, enemyList[i].getPlainText(), enemyList[i].getColor());
		}
	}
}

std::string Earth::helpText()
{
	return help;
}