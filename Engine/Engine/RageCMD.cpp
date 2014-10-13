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
	selection = true;
}

void RageCMD::update()
{
	if(selection){
		selection = false;
		help = "Select Skill to use.";
	}
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

	for(int i = 0; i<skillList.size(); i++){
		skillList[i]->checkOn();
		if(Engine::Input::instance()->check_mouse_button(0) 
			&& skillList[i]->isOn())
		{
			help = "Unleash your Rage on an enemy.";
			b->activeCMD = skillList[i];
			b->activeCMD->init();
			b->turnStatus = TURN_STATUS::CMD;
			break;
		}
	}
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
				help = "";
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &skillList[i]->getRect(), 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));

				// help text
				RECT tempRect;
				tempRect.left = 50;
				tempRect.top = 7;
				tempString = skillList[i]->helpText();
				tempWS = std::wstring(tempString.begin(),tempString.end());
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &tempRect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else{
				Engine::Text::instance()->font->DrawText(0, tempWS.c_str(), -1, &skillList[i]->getRect(), 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				selection = true;
			}
		
	}
}

std::string RageCMD::helpText()
{
	return help;
}
