#include "Inn.h"


Inn::Inn(void)
{
}


Inn::~Inn(void)
{
}

Inn* Inn::instance()
{
	static Inn inn;
	return &inn;
}

void Inn::init()
{
	//bg.setHandle("options");
	bg.setTranslate(300,180,0);
	bg.setScale(.7,.5,0);

	box.setHandle("blueBox");
	box.setTranslate(160,460,0);
	box.setScale(.7,.7,0);
	
	RData uiData[] = {
		{225, 0, 250, 200, 170, 465},	// back

	};
	for(int i = 0; i < INN_BUTTONS; i++) {
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
		buttons[i].setHandle("opButtons");
		//buttons[i].setTranslate(300,180,0);
		buttons[i].setScale(.4,.8,0);
	}
}

void Inn::shutdown()
{
}

int Inn::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();
	
	int _x = c->cursorPos.x;
	int _y = c->cursorPos.y;

	for(int i = 0; i < INN_BUTTONS; i++)
	{
		if(i>2) i = 7; // REMOVE : when Continue is implemented
		if(buttons[i].checkOn(_x,_y,4,1)) {
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
			if(input->check_mouse_button(0)){
				if(!input->check_button_down(DIK_9)){
					input->set_button(DIK_9,true);
					switch(i)
					{
					case 0: // BACK 
						return RETURN;
					default:
						break;
					}
				}
			} else input->set_button(DIK_9,false);
		}
		else
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
			
	}
	return 0;
}
void Inn::render()
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
				g->Draw2DObject(box);
				for(auto &button: buttons){
					g->Draw2DObject(button);
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