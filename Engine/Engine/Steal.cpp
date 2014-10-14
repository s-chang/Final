#include "Steal.h"
#include "Battle.h"

Steal::Steal(void) : Skill()
{
	name = "Steal";
	type = SKILL_TYPES::SUBTLETY;
	help = "Steal an item from the enemy. Stamina Cost: 20";
	cost = 20;
}


Steal::~Steal(void)
{
}

void Steal::init()
{
	stole = false;
	timer = 0;
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

void Steal::update()
{
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();
	
	if(stole){
		timer += Engine::Timer::instance()->getDT();
		if(timer > 1){
			b->activeCMD = NULL;
			b->turnStatus = TURN_STATUS::START;
			b->turnOrder.COUNTER++;
			help = "Steal an item from the enemy. Stamina Cost: 20";
		}
		return;
	}

	if(Lenn::instance()->getResource() < cost){
		help = "Sorry insufficient Stamina.";
		timer += Engine::Timer::instance()->getDT();
		if(timer > 1){
			b->activeCMD = NULL;
			b->turnStatus = TURN_STATUS::START;
			help = "Steal an item from the enemy. Stamina Cost: 20";
		}
		return;
	}

	help = "Select an enemy by clicking its name or right click to return";

	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->turnStatus = TURN_STATUS::START;
		help = "Steal an item from the enemy. Stamina Cost: 20";
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
							//check if you have stolen from this enemy
							if(b->stolenFrom[i]){
								help = "Nothing to Steal.";
							}
							else{
								b->stolenFrom[i] = true;
								getItem();
							}
							stole = true;
							Lenn::instance()->adjustResource(-cost);
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			enemyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
}


void Steal::render()
{
}

void Steal::text()
{
	for(unsigned int i = 0; i < enemyList.size(); i++){
		if(Battle::instance()->enemies[i].isAlive())
			Engine::Text::instance()->render(enemyList[i].getRect().top, 
			enemyList[i].getRect().left, enemyList[i].getPlainText(), enemyList[i].getColor());
	}
}

std::string Steal::helpText()
{
	return help;
}


void Steal::getItem(){
	int index = rand()%3;
	Item* item;

	switch(index)
	{
	case 0:
		item = ItemFactory::instance()->getItem("Potion");
		Player::instance()->addItem(item);
		help = "Stole a Potion from the enemy!";
		break;
	case 1:
		item = ItemFactory::instance()->getItem("Ether");
		Player::instance()->addItem(item);
		help = "Stole an Ether from the enemy!";
		break;
	case 2:
		item = ItemFactory::instance()->getItem("Revive");
		Player::instance()->addItem(item);
		help = "Stole a Revive from the enemy!";
		break;
	}	
}