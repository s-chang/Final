#include "Shop.h"
#include "Player.h"

Shop::Shop(void)
{
}


Shop::~Shop(void)
{
}

Shop* Shop::instance()
{
	static Shop s;
	return &s;
}

void Shop::init()
{
	bg.setHandle("shop");
	bg.setTranslate(300,180,0);
	bg.setScale(.8,.6,0);

	openWindow.setHandle("shopWindow");
	openWindow.setTranslate(300,180,0);
	openWindow.setScale(.8,.6,0);
	//openWindow.setColor(D3DCOLOR_ARGB(100,255,255,255));

	ItemWindow.setHandle("secondWindow");
	ItemWindow.setTranslate(300,180,0);
	ItemWindow.setScale(.8,.6,0);
	ItemWindow.setColor(D3DCOLOR_ARGB(200,255,255,255));
	
	SCDATA scdata[] = {
		{100.0f, 470.0f, 445,50,485,200,L"Buy"},
		{100.0f, 510.0f, 485,50,525,200,L"Sell"},
		{100.0f, 550.0f, 525,50,565,200,L"Back"},
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

	SCDATA tabData = {70.0f, 180.0f, 155,20,195,200,L"Spears"};
	wchar_t* names[] = {
		{L"Spears"},
		{L"Daggers"},
		{L"Staves"},
		{L"Armor"},
		{L"Accessories"},
		{L"Runes"},
		{L"Consumables"},
		};

	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(tabData.x,tabData.y+=30,0.0f);
		tempR.left = tabData.l;
		tempR.right = tabData.r;
		tempR.top = tabData.t+=30;
		tempR.bottom = tabData.b+=30;
		tempCommands.init();
		tempCommands.setText(names[i]);
		tempCommands.setRect(tempR);
		tabs.push_back(tempCommands);
	}

	state = SHOP_STATE::OPEN;
	help = false;
	insufficientFunds = false;
	helpText = "";
	page = 0;
	
	items.clear();
}

void Shop::shutdown()
{
}

int Shop::update()
{
	switch(checkList(buttons))
	{
	case 0: //BUY
		state = SHOP_STATE::BUY;
		items.clear();
		break;
	case 1: //SELL
		sellList();
		state = SHOP_STATE::SELL;
		break;
	case 2: //BACK
		state = SHOP_STATE::OPEN;
		return GameStates::RETURN;
		break;
	}
	if(state == SHOP_STATE::SELL)
		sellItems();
	if(state == SHOP_STATE::BUY || state == SHOP_STATE::DISPLAY_ITEMS){
		switch(checkList(tabs))
		{
		case 0:// Spears 
			Spears();
			break;
		case 1:// Daggers 
			Daggers();
			break;
		case 2:// Staves 
			Staves();
			break;
		case 3:// Armor 
			Armor();
			break;
		case 4:// Accessories
			Accessories();
			break; 
		case 5:// Runes 
			Runes(); 
			break;
		case 6:// Consumables 
			Consumables();
			break;
		}
		checkItems();
	}

	return 0;
}
void Shop::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	Engine::Graphics* g = Engine::Graphics::instance();
	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{
			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				g->Draw2DObject(bg);
				g->Draw2DObject(openWindow);

				if(state != SHOP_STATE::OPEN)
					g->Draw2DObject(ItemWindow);

				Engine::DX::instance()->getSprite()->End();
				RECT rect;
				rect.top = 50;
				rect.left = 70;
				if(!help && !insufficientFunds) {

					switch(state)
					{
					case SHOP_STATE::OPEN:
						Engine::Text::instance()->font->DrawText(0,L"Welcome! What can I do for you?", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case SHOP_STATE::BUY:
					case SHOP_STATE::DISPLAY_ITEMS:
						Engine::Text::instance()->font->DrawText(0,L"What are ya' buyin'?", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case SHOP_STATE::SELL:
						Engine::Text::instance()->font->DrawText(0,L"What are ya' sellin'?", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					}
				}
				if(help)
					displayItemStats(ItemFactory::instance()->getItem(helpText));
				if (insufficientFunds && !help)
					Engine::Text::instance()->font->DrawText(0,L"Insufficient Funds.", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				rect.top = 550;
				rect.left = 550;
				wchar_t tbuffer[64];
				swprintf_s(tbuffer, 64,L"Your Gold %d",Player::instance()->getGold());
				Engine::Text::instance()->font->DrawText(0,tbuffer, -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

				for(unsigned int i = 0; i < buttons.size(); i++)
					Engine::Text::instance()->render(buttons[i].getRect().top, 
					buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());

				if(state == SHOP_STATE::SELL){
					// render next button
					if(page + 8 < items.size()){
						Engine::Text::instance()->render(items[0].getRect().top, 
							items[0].getRect().left, items[0].getPlainText(), items[0].getColor());
					}
					if(page)
						Engine::Text::instance()->render(items[1].getRect().top, 
							items[1].getRect().left, items[1].getPlainText(), items[1].getColor());

					// check for which page
					int start = page + 2;
					for(unsigned int i = start; i < items.size() && i<start+8; i++) {
						Engine::Text::instance()->render(items[i].getRect().top, 
							items[i].getRect().left, items[i].getHandle(), items[i].getColor());
						RECT tempR = items[i].getRect();
						tempR.left += 170;
						Item* item = ItemFactory::instance()->getItem(items[i].getHandle());
						swprintf_s(tbuffer, 64,L"%d",item->getStats().price/2);
						delete item;
						Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &tempR, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}

				if(state != SHOP_STATE::SELL && (state == SHOP_STATE::BUY || state == SHOP_STATE::DISPLAY_ITEMS)){
					for(unsigned int i = 0; i < tabs.size(); i++)
						Engine::Text::instance()->render(tabs[i].getRect().top, 
							tabs[i].getRect().left, tabs[i].getPlainText(), tabs[i].getColor());
					for(unsigned int i = 0; i < items.size(); i++) {
						Engine::Text::instance()->render(items[i].getRect().top, 
						items[i].getRect().left, items[i].getHandle(), items[i].getColor());
						RECT tempR = items[i].getRect();
						tempR.left += 170;
						Item* item = ItemFactory::instance()->getItem(items[i].getHandle());
						swprintf_s(tbuffer, 64,L"%d",item->getStats().price);
						delete item;
						Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &tempR, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
			}
			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				g->drawCursor();
				Engine::DX::instance()->getSprite()->End();
			}
		}
		Engine::DX::instance()->getDevice()->EndScene();
	}
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}


void Shop::checkItems()
{
	bool idkHelp = false;
	for(unsigned int i = 0; i < items.size(); i++){
		if(items[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				items[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
				idkHelp = true;
				helpText = items[i].getHandle();
				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						Item* item = ItemFactory::instance()->getItem(items[i].getHandle());
						if(Player::instance()->getGold() >= item->getStats().price){
							insufficientFunds = false;
							//item->setAmount(1);
							Player::instance()->addItem(item);
							Player::instance()->adjustGold(-item->getStats().price);
						} //else helpText = 
						else
							insufficientFunds = true;
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else {
			items[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	help = idkHelp;
}

int Shop::checkList(std::vector<Drawable>& list)
{
	int returnable = 99;
	for(unsigned int i = 0; i < list.size(); i++){
		if(list[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				list[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);
						returnable = i;
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			list[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}
	return returnable;
}


void Shop::sellItems()
{
	
	bool idkHelp = false;
	for(unsigned int i = 0; i < items.size() && i < 2; i++){
		if(items[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				items[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						if(i) {// back
							page -= 4;
							if(page < 0)
								page = 0;
						}
						else { //next
							if(page + 8 < items.size())
								page += 4;
						}
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else {
			items[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}

	// check for which page
	int start = page + 2;

	for(unsigned int i = start; i < items.size() && i < start+8; i++){
		if(items[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				items[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
				idkHelp = true;
				helpText = items[i].getHandle();
				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);

						Item* item = ItemFactory::instance()->getItem(items[i].getHandle());
						Player::instance()->adjustGold(item->getStats().price/2);
						Player::instance()->removeItem(*item);
						delete item;

						sellList();
					}
				}
				else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else {
			items[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	help = idkHelp;
}

void Shop::sellList()
{
	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA nextData = {70.0f, 180.0f, 155,20,195,200,L"Next Page"};

	tempCommands.setTranslate(nextData.x,nextData.y+=40,0.0f);
	tempR.left = nextData.l;
	tempR.right = nextData.r;
	tempR.top = nextData.t+=40;
	tempR.bottom = nextData.b+=40;
	tempCommands.init();
	tempCommands.setText(nextData.name);
	tempCommands.setRect(tempR);
	items.push_back(tempCommands);

	tempCommands.setTranslate(nextData.x,nextData.y+=40,0.0f);
	tempR.left = nextData.l;
	tempR.right = nextData.r;
	tempR.top = nextData.t+=40;
	tempR.bottom = nextData.b+=40;
	tempCommands.init();
	tempCommands.setText(L"Back");
	tempCommands.setRect(tempR);
	items.push_back(tempCommands);

	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	std::vector<Item*>* tempInventory = Player::instance()->getInventory(); 
	
	for(int i = 0; i < tempInventory->size(); i++){
		if(i%8 == 0){
			scData.y = 180.0f;
			scData.t = 155;
			scData.b = 195;
		}
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(tempInventory->at(i)->getStats().name);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}

void Shop::Spears()
{
	std::string names[] = {
		"Weathered Spear",
		"Short Spear",
		"Spear",
		"Harpoon",
		"Lance",
		"Gae Bolg",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Daggers()
{
	std::string names[] = {
		"Chipped Dagger",
		"Knife",
		"Sting",
		"Needle",
		"Dagger",
		"Night's Bane",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Staves()
{
	std::string names[] = {
		"Splintered Staff",
		"Rod",
		"Staff",
		"Rod of Light",
		"Staff of Wisdom",
		"Iron Staff",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Armor()
{
	std::string names[] = {
		"Clothes",
		"Leather Armor",
		"Chain Mail",
		"Enchanted Robe",
		"Plate Armor",
		"Dragon Armor",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Accessories()
{
	std::string names[] = {
		"NONE",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Runes()
{
	std::string names[] = {
		"NONE",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}
void Shop::Consumables()
{
	std::string names[] = {
		"Potion",
		"Ether",
		"Revive",
		};

	items.clear();
	Drawable tempCommands;
	RECT tempR;
	SCDATA scData = {270.0f, 180.0f, 155,220,195,370,L"Handle"};
	for(int i = 0; i < sizeof(names)/sizeof(names[0]); i++){
		tempCommands.setTranslate(scData.x,scData.y+=40,0.0f);
		tempR.left = scData.l;
		tempR.right = scData.r;
		tempR.top = scData.t+=40;
		tempR.bottom = scData.b+=40;
		tempCommands.init();
		tempCommands.setText(scData.name);
		tempCommands.setHandle(names[i]);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}
}

void Shop::displayItemStats(Item* item)
{
	Engine::Text* t = Engine::Text::instance();
	RECT tempR;
	tempR.top = 50;
	tempR.left = 70;

	wchar_t tbuffer[64];
	std::string tempString;
	std::wstring tempWS = L"";

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
	//if(item->getStats().type != "Accessory" ||){
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
	//}

	delete item;
}