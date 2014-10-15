#include "ItemCMD.h"
#include "Battle.h"


ItemCMD::ItemCMD(void) : BattleCommand()
{
	name = "Item";
	help = "Use an item from your inventory";
	items.clear();
	itemSelected = false;
	useThis = NULL;
}


ItemCMD::~ItemCMD(void)
{
}


void ItemCMD::init()
{
	name = "Item";
	help = "Use an item from your inventory";
	itemSelected = false;
	if(useThis){
		delete useThis;
		useThis = NULL;
	}
	setList();

	allyList.clear();
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

void ItemCMD::update()
{
	help = "Select an item by clicking its name or right click to return";
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();

	if(itemSelected){
		b->renderNames = true;
		help = "Select an Ally by clicking its name or right click to return";
		checkAllies();
	}
	else{
		b->renderNames = false;
		checkItems();
	}
	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->renderNames = true;
		b->turnStatus = TURN_STATUS::START;
		help = "Use an item from your inventory";
		return;
	}

}

void ItemCMD::render()
{

}

void ItemCMD::text()
{
	if(itemSelected){
		for(unsigned int i = 0; i < allyList.size(); i++){
			Engine::Text::instance()->render(allyList[i].getRect().top, 
				allyList[i].getRect().left, allyList[i].getPlainText(), allyList[i].getColor());
		}
	}
	else{
		for(unsigned int i = 0; i < items.size(); i++)
		{
			if( items[i].getPlainText() == L"Handle"){
				Engine::Text::instance()->render(items[i].getRect().top, 
					items[i].getRect().left, items[i].getHandle(), items[i].getColor());
			}
			else
				Engine::Text::instance()->render(items[i].getRect().top, 
				items[i].getRect().left, items[i].getPlainText(), items[i].getColor());
		}
	}
}

std::string ItemCMD::helpText()
{
	return help;
}

void ItemCMD::setList()
{
	items.clear();
	SCDATA scdata = {520.0f, 475.0f, 450,470,490,620,L"NONE"};
	Drawable tempCommands;
	RECT tempR;

	std::vector<Item*> tempInventory;
	Player::instance()->getItemsOfType(tempInventory,"Item");

	if(tempInventory.empty()){
		tempCommands.setTranslate(scdata.x,scdata.y,0.0f);
		tempR.left = scdata.l;
		tempR.right = scdata.r;
		tempR.top = scdata.t;
		tempR.bottom = scdata.b;
		tempCommands.init();
		tempCommands.setText(scdata.name);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}

	scdata.y -= 30;
	scdata.t -= 30;
	scdata.b -= 30;

	for(unsigned int i = 0; i < tempInventory.size(); i++){
		tempCommands.setTranslate(scdata.x,scdata.y+=30,0.0f);
		tempR.left = scdata.l;
		tempR.right = scdata.r;
		tempR.top = scdata.t+=30;
		tempR.bottom = scdata.b+=30;
		tempCommands.init();
		tempCommands.setText(L"Handle");
		tempCommands.setHandle(tempInventory[i]->getStats().name);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}

}

void ItemCMD::checkItems()
{
	for(unsigned int i = 0; i < items.size(); i++){
		if(items[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				items[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						if(useThis){
							delete useThis;
							useThis = NULL;
						}
						useThis = ItemFactory::instance()->getItem(items[i].getHandle());
						itemSelected = true;
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else {
			items[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}
}
void ItemCMD::checkAllies(){
	for(unsigned int i = 0; i < allyList.size(); i++){
		if(allyList[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				allyList[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						useItem(Battle::instance()->all[i]);
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			allyList[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
}

void ItemCMD::useItem(Entity * who)
{
	if(!useThis){
		itemSelected = false;
		Battle::instance()->activeCMD = NULL;
		Battle::instance()->renderNames = true;
		Battle::instance()->turnStatus = TURN_STATUS::START;
		help = "Use an item from your inventory";
		return;
	}
	bool cant = true;
	if(useThis->getStats().name == "Potion")
	{
		if(who->isAlive()){
			if(who->getStats()->health < who->getStats()->maxHealth){
				who->adjustHealth(useThis->getStats().health);
				Player::instance()->removeItem(*useThis);
				cant = false;
			}
		}
	}
	if(useThis->getStats().name == "Ether")
	{
		if(who->getResource() < who->getMaxResource()){
			who->adjustResource(useThis->getStats().health);
			Player::instance()->removeItem(*useThis);
			cant = false;
		}
	}
	if(useThis->getStats().name == "Revive")
	{
		if(!who->isAlive()){
			who->adjustHealth(useThis->getStats().health);
			Player::instance()->removeItem(*useThis);
			cant = false;
		}
	}

	if(cant){
		itemSelected = false;
		Battle::instance()->activeCMD = NULL;
		Battle::instance()->renderNames = true;
		Battle::instance()->turnStatus = TURN_STATUS::START;
		help = "Use an item from your inventory";
		delete useThis;
		useThis = NULL;
		return;
	}

	itemSelected = false;
	Battle::instance()->activeCMD = NULL;
	Battle::instance()->renderNames = true;
	Battle::instance()->turnStatus = TURN_STATUS::START;
	Battle::instance()->turnOrder.COUNTER++;
	help = "Use an item from your inventory";
	delete useThis;
	useThis = NULL;
	//setList();
}