#include "RageCMD.h"
#include "Battle.h"
#include "Player.h"
#include "Skill.h"

RageCMD::RageCMD(void) : BattleCommand()
{
	name = "Rage";
	help = "Unleash your Rage on an enemy.";
}


RageCMD::~RageCMD(void)
{
}

void RageCMD::init()
{
	skillList.clear();
	Grem::instance()->getSkills(skillList,SKILL_TYPES::RAGE);

	//RECT tempR;
	//SCDATA scdata = { 70.0f, 445.0f, 420, 20, 460, 170, L"Handle"};

	int top = 440;
	int left = 470;
	for(int i = 0; i< skillList.size(); i++){
		skillList[i]->setRect(top,left);
		top+=30;
	}
}

void RageCMD::update()
{
	help = "Select Skill to use.";
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();
	b->renderNames = false;
	if(input->check_mouse_button(1)){	
		b->renderNames = true;
		b->activeCMD = NULL;
		b->turnStatus = TURN_STATUS::START;
		help = "Unleash your Rage on an enemy.";
		return;
	}
	
	//for(unsigned int i = 0; i < enemyList.size(); i++){
	//	if(enemyList[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
	//		Engine::Cursor::instance()->cursorPos.y, 3)){
	//			enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

	//			if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
	//				if(!Engine::Input::instance()->check_button_down(DIK_9)){
	//					Engine::Input::instance()->set_button(DIK_9, true);
	//					if(b->enemies[i].isAlive()){
	//						// if the enemy highlighted is alive then do dmg calculations
	//						Entity* player = b->all[b->turnOrder.COUNTER];
	//						Entity* enemy = &b->enemies[i];
	//						int atk = player->getStats()->attack + player->getItemStatsForSlot(SLOT::WEAPON)->atk;
	//						int def = enemy->getStats()->defense;
	//						int dmg = atk - def;
	//						if(dmg < 0)
	//							dmg = 0;
	//						enemy->adjustHealth(-dmg);

	//						b->dmg = dmg;
	//						b->turnStatus = TURN_STATUS::END;

	//						help = "Use basic attack on an enemy";
	//					}
	//				}
	//			}
	//			else Engine::Input::instance()->set_button(DIK_9, false);
	//	}
	//	else
	//		enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	//}
}

void RageCMD::render()
{
}

void RageCMD::text()
{
	for(unsigned int i = 0; i < skillList.size(); i++){
		//BattleCommand* tempCMD = e->getCommand(i);
		std::string tempString = skillList[i]->getName();
			std::wstring tempWS = std::wstring(tempString.begin(),tempString.end());
			if(skillList[i]->isOn()){
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &skillList[i]->getRect(), 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));

				// help text
				rect.left = 50;
				rect.top = 7;
				tempString = skillList[i]->helpText();
				tempWS = std::wstring(tempString.begin(),tempString.end());
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &skillList[i]->getRect(), 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		
	}
}

std::string RageCMD::helpText()
{
	return help;
}
