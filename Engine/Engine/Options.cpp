#include "Options.h"


Options::Options(void)
	:GameState()
{
}


Options::~Options(void)
{
}

Options* Options::instance()
{
	static Options op;
	return &op;
}

void Options::init()
{
	bg.setHandle("options");
	bg.setTranslate(300.0f,180.0f,0.0f);
	bg.setScale(.7f,.5f,0.0f);

	box.setHandle("blueBox");
	box.setTranslate(160.0f,460.0f,0.0f);
	box.setScale(.7f,.7f,0.0f);
	
	RData uiData[] = {
		{0, 0, 30, 200, 165, 70},		// credits
		{40, 50, 60, 120, 305, 170},	// -
		{35, 130, 65, 250, 495, 170},	// +
		{0, 0, 0, 0, 0, 0},	// TODO: Fullscreen
		{0, 0, 0, 0, 0, 0},	// TODO: window
		{0, 0, 0, 0, 0, 0},	// TODO: keyboard
		{0, 0, 0, 0, 0, 0},	// TODO: controller
		{225, 0, 250, 200, 170, 465},	// back

	};
	for(int i = 0; i < OPBUTTONS; i++) {
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
		buttons[i].setScale(.4f,.8f,0.0f);
	}
}

void Options::shutdown()
{
}

int Options::update()
{
	Engine::Cursor* c = Engine::Cursor::instance();
	Engine::Input* input = Engine::Input::instance();
	
	int _x = (int)c->cursorPos.x;
	int _y = (int)c->cursorPos.y;

	for(int i = 0; i < OPBUTTONS; i++)
	{
		if(i>2) i = 7; // REMOVE : when Continue is implemented
		if(buttons[i].checkOn((float)_x,(float)_y,4,1)) {
			buttons[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
			if(input->check_mouse_button(0)){
				if(!input->check_button_down(DIK_9)){
					input->set_button(DIK_9,true);
					switch(i)
					{
					case 0: // credits TODO: run credits
						break;
					case 1: // - TODO: lower volume
					case 2: // + TODO: raise volume
						break;
					case 3: // TODO: Fullscreen
					case 4: // TODO: window
					case 5: // TODO: keyboard
					case 6: // TODO: controller
					case 7: // back
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
void Options::render()
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