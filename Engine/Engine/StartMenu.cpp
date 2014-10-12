#include "StartMenu.h"

StartMenu::StartMenu(void) : GameState()
{
}

StartMenu* StartMenu::instance()
{
	static StartMenu menu;
	return &menu;
}

StartMenu::~StartMenu(void)
{
}

void StartMenu::init()
{
	bg.setHandle("startMenu");
	bg.setTranslate(300.0f,180.0f,0.0f);
	bg.setScale(.77f,.55f,0.0f);
	RData uiData[] = {
		{0, 0, 120, 500, 150, 280},
		{245, 0, 340, 500, 150, 350},
		{121, 0, 230, 500, 150, 420},
		{345, 0, 460, 300, 150, 500},
	};
	for(int i = 0; i < MENU_BUTTON_CNT; i++) {
		Drawable temp;
		RECT rect;
		// NewGame
		rect.top = uiData[i].t; 
		rect.left = uiData[i].l;
		rect.bottom =  uiData[i].b; 
		rect.right =  uiData[i].r;
		temp.setTranslate( uiData[i].x, uiData[i].y, 0);
		temp.setRect(rect);
		buttons[i]= temp;
		buttons[i].setHandle("menuButtons");
		//buttons[i].setTranslate(300,180,0);
		buttons[i].setScale(.5,.5,0);
	}

	// TODO: if we are initing the start menu or reiniting it we also need to reset entire game
	
}

void StartMenu::shutdown()
{
}

int StartMenu::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();

	int _x = (int)c->cursorPos.x;
	int _y = (int)c->cursorPos.y;

	for(int i = 0; i < MENU_BUTTON_CNT; i++)
	{
		if(i==1) i = 2; // REMOVE : when Continue is implemented
		if(buttons[i].checkOn((float)_x,(float)_y,3)) {
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
			// check for mouse click AND GO TO CORRECT STATE
			if(input->check_mouse_button(0)){
				if(!input->check_button_down(DIK_9)){
					input->set_button(DIK_9,true);
					switch(i)
					{
					case 0: // newgame
						return NEWGAME;
					case 1: //continue
						return CONTINUE;
					case 2: // Options
						return OPTIONS;
					case 3: // Quit
						exit(1); // change exit method
					default:
						break;
					}
				}
			} else input->set_button(DIK_9,false);
		}
		else
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}


	///////////////////////////////////////////////
	// debug instaswitch to battle
	///////////////////////////////////////////////
	if(input->push_button(DIK_B))
		return BATTLE;

	return 0;
}
void StartMenu::render()
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

				for(int i = 0; i < MENU_BUTTON_CNT; i++){
					if(i==1) i = 2; // REMOVE : when Continue is implemented
					g->Draw2DObject(buttons[i]);
				}

				// draw cursor last
				g->drawCursor();
				Engine::DX::instance()->getSprite()->End();

				//Engine::Text::instance()->render(0,0);
			}
		}
		Engine::DX::instance()->getDevice()->EndScene();
	}
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}
