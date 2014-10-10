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

							switch(i)
							{

							}
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

				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////
				for(unsigned int i = 0; i < buttons.size(); i++)
				{
					Engine::Text::instance()->render(buttons[i].getRect().top, 
						buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());
				}

				if(state == EQUIPSTATE::SHOW_ITEMS)
					for(unsigned int i = 0; i < equipped.size(); i++){
						if( equipped[i].getPlainText() == L"Handle"){
							Engine::Text::instance()->render(equipped[i].getRect().top, 
								equipped[i].getRect().left, equipped[i].getHandle(), equipped[i].getColor());
							if(equipped[i].getColor() == D3DCOLOR_ARGB(255,255,255,0)){
								displayItemStats(true);
								//displayItemStats(false); // for testing
							}
						}
						else
							Engine::Text::instance()->render(equipped[i].getRect().top, 
							equipped[i].getRect().left, equipped[i].getPlainText(), equipped[i].getColor());
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

}

void EquipScreen::setState(int state)
{
	this->state = state;
	slot = 99;
}

void EquipScreen::displayItemStats(bool top)
{
	Engine::Text* t = Engine::Text::instance();
	RECT tempR;
	tempR.left = 260;

	wchar_t tbuffer[64];
	std::string tempString;
	std::wstring tempWS = L"";

	if(top) tempR.top = 55; 
	else	tempR.top = 440; 

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
	/* draw text as string or wchar_t*

	tempWS = std::wstring(tempString.begin(),tempString.end());

	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
	DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	swprintf_s(tbuffer, 64,L"%d/%d",enemy.getStats()->health,enemy.getStats()->maxHealth);

	t->font->DrawText(0, tbuffer, -1, &rect, 
	DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	*/
}