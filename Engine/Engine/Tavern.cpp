#include "Tavern.h"


Tavern::Tavern(void)
{
}


Tavern::~Tavern(void)
{
}

Tavern* Tavern::instance()
{
	static Tavern t;
	return &t;
}

void Tavern::init()
{
	bg.setHandle("tavern");
	bg.setTranslate(300,180,0);
	bg.setScale(.8,.6,0);

	openWindow.setHandle("tavernWindow");
	openWindow.setTranslate(300,180,0);
	openWindow.setScale(.8,.6,0);
	//openWindow.setColor(D3DCOLOR_ARGB(100,255,255,255));

	secondWindow.setHandle("secondWindow");
	secondWindow.setTranslate(300,180,0);
	secondWindow.setScale(.8,.6,0);
	secondWindow.setColor(D3DCOLOR_ARGB(200,255,255,255));
	
	SCDATA scdata[] = {
		{100.0f, 470.0f, 445,50,485,200,L"Tutorials"},
		{100.0f, 510.0f, 485,50,525,200,L"Rumors"},
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
	state = TAVERN_STATE::OPEN;
}

void Tavern::shutdown()
{
}

int Tavern::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();
	
	int _x = c->cursorPos.x;
	int _y = c->cursorPos.y;

	for(unsigned int i = 0; i < buttons.size(); i++){
		if(buttons[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3)){
				buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

				if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON)){
					if(!Engine::Input::instance()->check_button_down(DIK_9)){
						Engine::Input::instance()->set_button(DIK_9, true);

						switch(i)
						{
						case 0: //Tutorials
							state = TAVERN_STATE::TUTORIALS;
							break;
						case 1: //Rumors
							state = TAVERN_STATE::RUMORS;
							break;
						case 2: //BACK
							state = TAVERN_STATE::OPEN;
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
void Tavern::render()
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
				if(state > TAVERN_STATE::RUMORS)
					g->Draw2DObject(secondWindow);

				Engine::DX::instance()->getSprite()->End();

				//Engine::Text::instance()->render(0,0);
				for(unsigned int i = 0; i < buttons.size(); i++)
				{
					Engine::Text::instance()->render(buttons[i].getRect().top, 
						buttons[i].getRect().left, buttons[i].getPlainText(), buttons[i].getColor());
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