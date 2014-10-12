#include "Shop.h"


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
	bg.setTranslate(300.0f,180.0f,0.0f);
	bg.setScale(.8f,.6f,0.0f);

	openWindow.setHandle("shopWindow");
	openWindow.setTranslate(300,180,0);
	openWindow.setScale(.8f,.6f,0.0f);
	//openWindow.setColor(D3DCOLOR_ARGB(100,255,255,255));

	ItemWindow.setHandle("secondWindow");
	ItemWindow.setTranslate(300,180,0);
	ItemWindow.setScale(.8f,.6f,0.0f);
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

	for(int i = 0; i < TABS; i++){
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
}

void Shop::shutdown()
{
}

int Shop::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();
	
	int _x = (int)c->cursorPos.x;
	int _y = (int)c->cursorPos.y;

	for(unsigned int i = 0; i < buttons.size(); i++){
		if(buttons[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);

						switch(i)
						{
						case 0: //BUY
							state = SHOP_STATE::BUY;
							break;
						case 1: //SELL
							state = SHOP_STATE::SELL;
							break;
						case 2: //BACK
							state = SHOP_STATE::OPEN;
							return GameStates::RETURN;
							break;
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

				if(!help){
					RECT rect;
					rect.top = 50;
					rect.left = 70;
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
	
				for(unsigned int i = 0; i < buttons.size(); i++)
					Engine::Text::instance()->render(buttons[i].getRect().top, 
						buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());

				if(state != SHOP_STATE::SELL && (state == SHOP_STATE::BUY || state == SHOP_STATE::DISPLAY_ITEMS))
					for(unsigned int i = 0; i < tabs.size(); i++)
						Engine::Text::instance()->render(tabs[i].getRect().top, 
							tabs[i].getRect().left, tabs[i].getPlainText(), tabs[i].getColor());
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
