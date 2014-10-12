#include "Tavern.h"
#include "Player.h"

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
	bg.setTranslate(300.0f,180.0f,0.0f);
	bg.setScale(.8f,.6f,0.0f);

	openWindow.setHandle("tavernWindow");
	openWindow.setTranslate(300.0f,180.0f,0.0f);
	openWindow.setScale(.8f,.6f,0.0f);
	//openWindow.setColor(D3DCOLOR_ARGB(100,255,255,255));

	secondWindow.setHandle("secondWindow");
	secondWindow.setTranslate(300.0f,180.0f,0.0f);
	secondWindow.setScale(.8f,.6f,0.0f);
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
	help = false;
	rewarded = false;
}

void Tavern::shutdown()
{
}

int Tavern::update()
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
						case 0: //Tutorials
							state = TAVERN_STATE::TUTORIALS;
							break;
						case 1: //Rumors
							state = TAVERN_STATE::RUMORS;
							if(Player::instance()->hasCompletedtenth())
								reward();
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

				if(!help){
					RECT rect;
					rect.top = 50;
					rect.left = 70;
					switch(state)
					{
					case TAVERN_STATE::OPEN:
						Engine::Text::instance()->font->DrawText(0,L"Yo, What can I get you!", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case TAVERN_STATE::TUTORIALS:
					case TAVERN_STATE::DISPLAY:
						Engine::Text::instance()->font->DrawText(0,L"Needing some help?", -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case TAVERN_STATE::RUMORS:
						if(Player::instance()->hasCompletedtenth()){
							Engine::Text::instance()->font->DrawText(0,L"Someone heard you slayed The Beast and left you a reward!\n Check your inventory", -1, &rect, 
								DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
							rewarded = true;
						}
						else 
							Engine::Text::instance()->font->DrawText(0,L"Sorry nothin new check back later.", -1, &rect, 
								DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					}
				}

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

void Tavern::reward()
{
	if(rewarded)
		return;
	Player::instance()->addItem(ItemFactory::instance()->getItem("Luin of Celtchar"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Gungnir"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Shiv of Titans"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Death and Deceit"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Ancient's Staff"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Save the Queen"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Falcon Cloak"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Tarkappe"));
	Player::instance()->addItem(ItemFactory::instance()->getItem("Green Armor"));
}