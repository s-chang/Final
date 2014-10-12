#include "StatusScreen.h"


StatusScreen::StatusScreen(void)
{
}


StatusScreen::~StatusScreen(void)
{
}

StatusScreen* StatusScreen::instance()
{
	static StatusScreen menu;
	return &menu;
}
void StatusScreen::init()
{
	who = 0;

	//Init background image
	background.init();
	background.setHandle("statScreen");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	//Init Portraits
	Drawable temp;
	temp.init();
	for(int i = 0; i<3; i++)
	{
		temp.setTranslate(310,210,0);
		temp.setScale(0.4f, 0.4f, 0.0f);
		portraits.push_back(temp);
	}
	portraits[0].setHandle("gremFullPic");
	portraits[1].setHandle("lennFullPic");
	portraits[2].setHandle("lazFullPic");

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
}

void StatusScreen::shutdown()
{

}

int StatusScreen::update()
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
					case 1: //Grem 0
						who = 0;
						break;
					case 2: //Lenn 1
						who = 1;
						break;
					case 3: //Laz 2
						who = 2;
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

void StatusScreen::render()
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

				if(who >= 0 && who < (int)portraits.size())
					g->Draw2DObject(portraits[who]);

				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////
				for(unsigned int i = 0; i < buttons.size(); i++)
				{
					Engine::Text::instance()->render(buttons[i].getRect().top, 
						buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());
				}

				switch(who)
				{
				case 0:
					renderStats(Grem::instance());
					break;
				case 1:
					renderStats(Lenn::instance());
					break;
				case 2:
					renderStats(Laz::instance());
					break;
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

void StatusScreen::renderStats(Entity* e)
{
	Engine::Text* t = Engine::Text::instance();

	RECT rect;
	rect.left = 510;
	rect.top = 110;
	wchar_t tbuffer[64];

	Stats* stats = e->getStats();

	swprintf_s(tbuffer, 64,L"Level           %d",stats->level);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Health         %d/%d",stats->health,stats->maxHealth);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Attack          %d",stats->attack);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Magic          %d",stats->magic);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Defence       %d",stats->defense);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Resistance   %d",stats->defense);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"Speed           %d",stats->speed);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"XP                 %d",stats->xp);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top+=40;
	swprintf_s(tbuffer, 64,L"XP To Level %d",e->getXpToLevel());
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}