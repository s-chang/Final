#include "InventoryScreen.h"
#include "Player.h"

InventoryScreen::InventoryScreen(void)
{
}


InventoryScreen::~InventoryScreen(void)
{
}

InventoryScreen* InventoryScreen::instance()
{
	static InventoryScreen menu;
	return &menu;
}
void InventoryScreen::init()
{
	//Init background image
	background.init();
	background.setHandle("invScreen");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	SCDATA scdata[] = {
		{100.0f, 580.0f, 555,50,595,200,L"Back"},
		{300.0f, 80.0f, 55,250,95,400,L"Use"},
		{500.0f, 80.0f, 55,450,95,600,L"Sort"}
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

}

void InventoryScreen::shutdown()
{

}

int InventoryScreen::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();
	
	for(unsigned int i = 0; i < buttons.size(); i++)
	{
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
					}
				}
			}
			else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}

	return 0;
}

void InventoryScreen::render()
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
				for(unsigned int i = 0; i < items.size(); i++)
				{
					if( items[i].getPlainText() == L"Handle"){
						displayItem(i);
					}
					else
						Engine::Text::instance()->render(items[i].getRect().top, 
							items[i].getRect().left, items[i].getPlainText(), items[i].getColor());
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

void InventoryScreen::setList()
{
	items.clear();
	SCDATA scdata = {300.0f, 180.0f, 155,250,195,400,L"NONE"};
	Drawable tempCommands;
	RECT tempR;

	std::vector<Item*>* tempInventory = Player::instance()->getInventory();
	if(tempInventory->empty()){
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

	for(int i = 0; i < tempInventory->size(); i++){
		if(i%3 == 0){
			scdata.y += 30;
			scdata.t += 30;
			scdata.b += 30;

			scdata.x = 300.0f - 170;
			scdata.l = 250 - 170;
			scdata.r = 400 - 170;
		}

		tempCommands.setTranslate(scdata.x+=170,scdata.y,0.0f);
		tempR.left = scdata.l+=170;
		tempR.right = scdata.r+=170;
		tempR.top = scdata.t;
		tempR.bottom = scdata.b;
		tempCommands.init();
		tempCommands.setText(L"Handle");
		tempCommands.setHandle(tempInventory->at(i)->getStats().name);
		tempCommands.setRect(tempR);
		items.push_back(tempCommands);
	}

}
void InventoryScreen::displayItem(int index)
{
	Item* item = Player::instance()->getInventory()->at(index);
	wchar_t tbuffer[64];
	RECT rect = items[index].getRect();

	Engine::Text::instance()->render(rect.top, rect.left, 
		items[index].getHandle(), items[index].getColor());
	if(item->getStats().type == "Item" && item->getAmount() > 1){
		swprintf_s(tbuffer, 64,L"%d",item->getAmount());
		rect.left +=70;
		Engine::Text::instance()->font->DrawText(0,tbuffer, -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, items[index].getColor());
	}
}