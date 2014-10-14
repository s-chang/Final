#include "EquipScreen.h"
#include "Player.h"


EquipScreen::EquipScreen(void)
{
}


EquipScreen::~EquipScreen(void)
{
}

EquipScreen* EquipScreen::instance()
{
	static EquipScreen menu;
	return &menu;
}
void EquipScreen::init()
{
	equipped.clear();
	available.clear();
	int who = 0;
	state = EQUIPSTATE::START;
	slot = 99;

	//Init background image
	background.init();
	background.setHandle("equipScreen");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	background2.init();
	background2.setHandle("ES2");
	background2.setTranslate(310,180,0);
	background2.setScale(0.8f, 0.6f, 0.0f);

	background3.init();
	background3.setHandle("ES3");
	background3.setTranslate(310,180,0);
	background3.setScale(0.8f, 0.6f, 0.0f);

	// init names as buttons
	SCDATA scdata[] = {
		{100.0f, 580.0f, 555,50,595,200,L"Back"},
		{100.0f, 180.0f, 155,50,195,200,L"Grem"},
		{100.0f, 280.0f, 255,50,295,200,L"Lenn"},
		{100.0f, 380.0f, 355,50,395,200,L"Lazarus"},
	};
	Drawable tempCommands;
	RECT tempR;

	for(int i = 0; i<sizeof(scdata)/sizeof(scdata[0]); i++){
		tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
		tempR.left = scdata[i].l;
		tempR.right = scdata[i].r;
		tempR.top = scdata[i].t;
		tempR.bottom = scdata[i].b;
		tempCommands.init();
		tempCommands.setText(scdata[i].name);
		tempCommands.setRect(tempR);
		buttons.push_back(tempCommands);
	}
	//setItems(who);
}

void EquipScreen::shutdown()
{

}

int EquipScreen::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();

	/////////////////////////////////////////////////////////////////////////////////////////
	// Main Button List
	/////////////////////////////////////////////////////////////////////////////////////////

	for(unsigned int i = 0; i < buttons.size(); i++){
		if(buttons[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);

						switch(i)
						{
						case 0: //back
							return GameStates::RETURN;
						case 1: //Grem 0
							who = 0;
							setItems(who);
							break;
						case 2: //Lenn 1
							who = 1;
							setItems(who);
							break;
						case 3: //Laz 2
							who = 2;
							setItems(who);
							break;
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}


	/////////////////////////////////////////////////////////////////////////////////////////
	// Equipped List
	/////////////////////////////////////////////////////////////////////////////////////////

	if(state == EQUIPSTATE::SHOW_ITEMS) {
		for(unsigned int i = 0; i < equipped.size(); i++){
			if(equipped[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
				Engine::Cursor::instance()->cursorPos.y, 3)){
					equipped[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
					slot = i;
					if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
						if(!Engine::Input::instance()->check_button_down(DIK_9)){
							Engine::Input::instance()->set_button(DIK_9, true);
							setAvailable(who,i);
							state = EQUIPSTATE::SHOW_AVAILABLE;
						}
					}
					else Engine::Input::instance()->set_button(DIK_9, false);
			}
			else equipped[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Available List
	////////////////////////////////////////////////////////////////////////////////////////
	if(state == EQUIPSTATE::SHOW_AVAILABLE) {
		for(unsigned int i = 0; i < available.size(); i++){
			if(available[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
				Engine::Cursor::instance()->cursorPos.y, 3)){
					available[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
					if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
						if(!Engine::Input::instance()->check_button_down(DIK_9)){
							if(available[i].getPlainText() == L"Handle"){
								//swap out equipment
								Item* newItem = NULL;
								newItem = ItemFactory::instance()->getItem(available[i].getHandle());
								switch(who)
								{
								case 0:
									Player::instance()->addItem(Grem::instance()->getItem(slot));
									Player::instance()->removeItem(*newItem);
									Grem::instance()->equipItem(newItem,slot);
									setItems(who);
									break;
								case 1:
									Player::instance()->addItem(Lenn::instance()->getItem(slot));
									Player::instance()->removeItem(*newItem);
									Lenn::instance()->equipItem(newItem,slot);
									setItems(who);
									break;
								case 2:
									Player::instance()->addItem(Laz::instance()->getItem(slot));
									Player::instance()->removeItem(*newItem);
									Laz::instance()->equipItem(newItem,slot);
									setItems(who);
									break;
								}
							}
						}
					}
					else Engine::Input::instance()->set_button(DIK_9, false);
			}
			else available[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}


	return 0;
}

void EquipScreen::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	Engine::Graphics* g = Engine::Graphics::instance();

	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{
			/////////////////////////////////////////
			// 3D objects
			/////////////////////////////////////////

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				/////////////////////////////////////////
				// 2D objects
				/////////////////////////////////////////

				g->Draw2DObject(background);
				if(state > EQUIPSTATE::START)
					g->Draw2DObject(background2);
				if(state == EQUIPSTATE::SHOW_AVAILABLE)
					g->Draw2DObject(background3);

				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////
				for(unsigned int i = 0; i < buttons.size(); i++)
				{
					Engine::Text::instance()->render(buttons[i].getRect().top, 
						buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());
				}

				if(state > EQUIPSTATE::START){
					for(unsigned int i = 0; i < equipped.size(); i++){
						if( equipped[i].getPlainText() == L"Handle"){
							Engine::Text::instance()->render(equipped[i].getRect().top, 
								equipped[i].getRect().left, equipped[i].getHandle(), equipped[i].getColor());
							if(equipped[i].getColor() == D3DCOLOR_ARGB(255,255,255,0)){
								Item* item = NULL;
								switch(who)
								{
								case 0:
									item = Grem::instance()->getItem(slot);
									break;
								case 1:
									item = Lenn::instance()->getItem(slot);
									break;
								case 2:
									item = Laz::instance()->getItem(slot);
									break;
								}
								displayItemStats(true,item);
							}
						}
						else
							Engine::Text::instance()->render(equipped[i].getRect().top, 
							equipped[i].getRect().left, equipped[i].getPlainText(), equipped[i].getColor());
					}
				}

				if(state == EQUIPSTATE::SHOW_AVAILABLE){
					for(unsigned int i = 0; i < available.size(); i++){
						if( available[i].getPlainText() == L"Handle"){
							Engine::Text::instance()->render(available[i].getRect().top, 
								available[i].getRect().left, available[i].getHandle(), available[i].getColor());
							if(available[i].getColor() == D3DCOLOR_ARGB(255,255,255,0)){
								Item* item = NULL;
								item = ItemFactory::instance()->getItem(available[i].getHandle());
								displayItemStats(false,item);
								delete item;
							}
						}
						else
							Engine::Text::instance()->render(available[i].getRect().top, 
							available[i].getRect().left, available[i].getPlainText(), available[i].getColor());
					}
				}
			}

			//////////////////////////////////////////////////
			// Cursor
			//////////////////////////////////////////////////

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK))){
				g->drawCursor();
				Engine::DX::instance()->getSprite()->End();
			}
		}
		Engine::DX::instance()->getDevice()->EndScene();
	}
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}


void EquipScreen::setItems(int who)
{
	equipped.clear();
	state = EQUIPSTATE::SHOW_ITEMS;

	SCDATA scdata[] = {
		{320.0f, 230.0f, 205,270,245,420,L"NONE"},
		{320.0f, 260.0f, 235,270,275,420,L"NONE"},
		{320.0f, 290.0f, 265,270,305,420,L"NONE"},
		{320.0f, 320.0f, 295,270,335,420,L"NONE"},
		{320.0f, 350.0f, 325,270,365,420,L"NONE"},
		{320.0f, 380.0f, 355,270,395,420,L"NONE"},
	};
	Drawable tempCommands;
	RECT tempR;

	switch(who)
	{
	case 0:
		for(int i = 0; i<sizeof(scdata)/sizeof(scdata[0]); i++){
			tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
			tempR.left = scdata[i].l;
			tempR.right = scdata[i].r;
			tempR.top = scdata[i].t;
			tempR.bottom = scdata[i].b;
			tempCommands.init();
			if(Grem::instance()->getItem(i) == NULL)
				tempCommands.setText(scdata[i].name);
			else {
				tempCommands.setText(L"Handle");
				tempCommands.setHandle(Grem::instance()->getItem(i)->getStats().name);
			}
			tempCommands.setRect(tempR);
			equipped.push_back(tempCommands);
		}
		break;
	case 1:
		for(int i = 0; i<sizeof(scdata)/sizeof(scdata[0]); i++){
			tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
			tempR.left = scdata[i].l;
			tempR.right = scdata[i].r;
			tempR.top = scdata[i].t;
			tempR.bottom = scdata[i].b;
			tempCommands.init();
			if(Lenn::instance()->getItem(i) == NULL)
				tempCommands.setText(scdata[i].name);
			else {
				tempCommands.setText(L"Handle");
				tempCommands.setHandle(Lenn::instance()->getItem(i)->getStats().name);
			}
			tempCommands.setRect(tempR);
			equipped.push_back(tempCommands);
		}
		break;
	case 2:
		for(int i = 0; i<sizeof(scdata)/sizeof(scdata[0]); i++){
			tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
			tempR.left = scdata[i].l;
			tempR.right = scdata[i].r;
			tempR.top = scdata[i].t;
			tempR.bottom = scdata[i].b;
			tempCommands.init();
			if(Laz::instance()->getItem(i) == NULL)
				tempCommands.setText(scdata[i].name);
			else {
				tempCommands.setText(L"Handle");
				tempCommands.setHandle(Laz::instance()->getItem(i)->getStats().name);
			}
			tempCommands.setRect(tempR);
			equipped.push_back(tempCommands);
		}
		break;
	}
}
void EquipScreen::setAvailable(int who, int slot)
{
	available.clear();
	SCDATA scdata = {600.0f, 205.0f, 180,550,220,700,L"NONE"};
	Drawable tempCommands;
	RECT tempR;
	std::vector<Item*> itemList;
	std::string tempString;

	switch(slot)
	{
	case 0:
		switch(who)
		{
		case 0:
			Player::instance()->getItemsOfType(itemList,"Spear");
			break;
		case 1:
			Player::instance()->getItemsOfType(itemList,"Dagger");
			break;
		case 2:
			Player::instance()->getItemsOfType(itemList,"Staff");
			break;
		}
		break;
	case 1:
		Player::instance()->getItemsOfType(itemList,"Armor");
		break;
	case 2:
	case 3:
		Player::instance()->getItemsOfType(itemList,"Rune");
		break;
	case 4:
	case 5:
		Player::instance()->getItemsOfType(itemList,"Accessory");
		break;
	}
	for(int i = 0; i< itemList.size(); i++){
		tempCommands.setTranslate(scdata.x,scdata.y+=25,0.0f);
		tempR.left = scdata.l;
		tempR.right = scdata.r;
		tempR.top = scdata.t+=25;
		tempR.bottom = scdata.b+=25;
		tempCommands.init();
		tempCommands.setText(L"Handle");
		tempCommands.setHandle(itemList[i]->getStats().name);
		tempCommands.setRect(tempR);
		available.push_back(tempCommands);
	}

	if(itemList.empty()){
		tempCommands.setTranslate(scdata.x,scdata.y+=25,0.0f);
		tempR.left = scdata.l;
		tempR.right = scdata.r;
		tempR.top = scdata.t+=25;
		tempR.bottom = scdata.b+=25;
		tempCommands.init();
		tempCommands.setText(scdata.name);
		tempCommands.setRect(tempR);
		available.push_back(tempCommands);
	}

}

void EquipScreen::setState(int state)
{
	this->state = state;
	slot = 99;
}

void EquipScreen::displayItemStats(bool top, Item* item)
{
	Engine::Text* t = Engine::Text::instance();
	RECT tempR;
	tempR.left = 260;

	wchar_t tbuffer[64];
	std::string tempString;
	std::wstring tempWS = L"";

	if(top) tempR.top = 55; 
	else	tempR.top = 440; 

	// write name and description and any stat thats not 0;

	// name
	tempString = item->getStats().name;
	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &tempR, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	// description
	tempR.top += 30;
	tempString = item->getStats().description;
	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &tempR, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	//stats
	// only if it's not rune or accessory
	if(slot < 2){
		/////// Attack
		tempR.top += 30;
		int stat = item->getStats().atk;
		if(stat){
			swprintf_s(tbuffer, 64,L"Atk %d",stat);
			t->font->DrawText(0, tbuffer, -1, &tempR, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		///////

		/////// magic
		tempR.left += 100;
		stat = item->getStats().mag;
		if(stat){
			swprintf_s(tbuffer, 64,L"Mag %d",stat);
			t->font->DrawText(0, tbuffer, -1, &tempR, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		///////

		/////// Defense
		tempR.left += 100;
		stat = item->getStats().def;
		if(stat){
			swprintf_s(tbuffer, 64,L"Def %d",stat);
			t->font->DrawText(0, tbuffer, -1, &tempR, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		///////

		/////// resist
		tempR.left += 100;
		stat = item->getStats().res;
		if(stat){
			swprintf_s(tbuffer, 64,L"Res %d",stat);
			t->font->DrawText(0, tbuffer, -1, &tempR, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		///////

		/////// speed
		tempR.left += 100;
		stat = item->getStats().spd;
		if(stat){
			swprintf_s(tbuffer, 64,L"Spd %d",stat);
			t->font->DrawText(0, tbuffer, -1, &tempR, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		///////
	}

}