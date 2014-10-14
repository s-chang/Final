#include "Wind.h"
#include "Battle.h"

Wind::Wind(void) : Skill()
{
	name = "Wind";
	type = SKILL_TYPES::ELEMENTAL;
	help = "Healing winds. Mana Cost: 7";
	cost = 7;
	timer = 0;
}


Wind::~Wind(void)
{
}

void Wind::init()
{
	allyList.clear();
	timer = 0;

	Drawable tempCommands;
	RECT tempR;
	//rect.left = 470;
	//rect.top = 450;
	SCDATA scdata[] = { 
		{ 520.0f, 475.0f, 450, 470, 490, 570, L"Grem"},
		{ 520.0f, 520.0f, 495, 470, 535, 570, L"Lenn"},
		{ 520.0f, 565.0f, 540, 470, 580, 570, L"Lazarus"},
	};
	//SCDATA scdata = { 70.0f, 445.0f, 420, 20, 460, 1070, L"Slime"};
	for(int i = 0; i < sizeof(scdata)/sizeof(scdata[0]); i++){
		tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
		tempR.left = scdata[i].l;
		tempR.right = scdata[i].r;
		tempR.top = scdata[i].t;
		tempR.bottom = scdata[i].b;
		tempCommands.init();
		tempCommands.setText(scdata[i].name);
		tempCommands.setRect(tempR);
		allyList.push_back(tempCommands);
	}
}

void Wind::update()
{
	if(allyList.empty())
		return;

	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();

	if(Laz::instance()->getResource() < cost){
		help = "Sorry insufficient Mana.";
		timer += Engine::Timer::instance()->getDT();
		if(timer > 1){
			b->activeCMD = NULL;
			b->turnStatus = TURN_STATUS::START;
			help = "Healing winds. Mana Cost: 7";
		}
		return;
	}

	help = "Select an Ally by clicking its name or right click to return";

	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->turnStatus = TURN_STATUS::START;
		help = "Healing winds. Mana Cost: 7";
		return;
	}

	for(unsigned int i = 0; i < allyList.size(); i++){
		if(allyList[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				allyList[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						Entity* player = b->all[i];
						if(player->isAlive()){
							player->adjustHealth(player->getStats()->maxHealth/3);
							Laz::instance()->adjustResource(-cost);
							b->turnStatus = TURN_STATUS::END;
							help = "Healing winds. Mana Cost: 7";
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			allyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
}


void Wind::render()
{
}

void Wind::text()
{
	if(allyList.empty())
		return;

	for(unsigned int i = 0; i < allyList.size(); i++){
		if(Battle::instance()->all[i]->isAlive())
			Engine::Text::instance()->render(allyList[i].getRect().top, 
				allyList[i].getRect().left, allyList[i].getPlainText(), allyList[i].getColor());
	}
}

std::string Wind::helpText()
{
	return help;
}