#include "InventoryScreen.h"


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
	getNewList = true;
	//Init background image
	background.init();
	background.setHandle("invScreen");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	SCDATA scdata[] = {
		{100.0f, 580.0f, 555,50,595,200,L"Back"},
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
	
	if(getNewList){
		//get list or items
		getNewList = false;
	}
	
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

