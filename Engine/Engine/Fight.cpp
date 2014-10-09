#include "Fight.h"
#include "Battle.h"

Fight::Fight(void) : BattleCommand()
{
	name = "Fight";
	help = "Use basic attack on an enemy";
	enemyHighlight = -1;
	top = 450;
	left = 20;
	r2.top = top;
	r2.left = left;
}


Fight::~Fight(void)
{
}

void Fight::init()
{
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
	if(c->cursorPos.x > left+15 && c->cursorPos.x < left+100){

		if(c->cursorPos.y > top+15 && c->cursorPos.y < top+40){
			enemyHighlight = 0;
			r2.top = top;
		}
		else if(c->cursorPos.y > top+60 && c->cursorPos.y < top+100)
		{
			enemyHighlight = 1;
			r2.top = top + 45;
		}
		else if(c->cursorPos.y > top+105 && c->cursorPos.y < top+145){
			enemyHighlight = 2;
			r2.top = top + 90;
		}
	}
	else
		enemyHighlight = -1;

	if(input->check_mouse_button(0)){
		if(enemyHighlight >=0 && enemyHighlight <=3){
			if(b->enemies[enemyHighlight].isAlive()){
				// if the enemy highlighted is alive then do dmg calculations
				Entity* player = b->all[b->turnOrder.COUNTER];
				Entity* enemy = &b->enemies[enemyHighlight];
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
}

void Fight::render()
{
}

void Fight::text()
{
	if(enemyHighlight >=0 && enemyHighlight <=3){
		Entity* e = &Battle::instance()->enemies[enemyHighlight];
		if(e->isAlive()){
		std::string tempString = e->getName();
		std::wstring tempWS = L"";
		tempWS = std::wstring(tempString.begin(),tempString.end());

		Engine::Text* t = Engine::Text::instance();
		t->font->DrawText(0, tempWS.c_str(), -1, &r2, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
		}
	}
}

std::string Fight::helpText()
{
	return help;
}
