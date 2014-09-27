#include "Battle.h"
#include "Tower.h"


Battle::Battle(void)
{
}


Battle::~Battle(void)
{
}

Battle* Battle::instance()
{
	static Battle tower;
	return &tower;
}

void Battle::init()
{
}

void Battle::shutdown()
{
}

int Battle::update()
{
	return 0;
}
void Battle::render()  
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

				//g->Draw2DObject(helpBar);

				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////

				Engine::Text* t = Engine::Text::instance();

				RECT rect;
				rect.left = 200;
				rect.top = 200;
				wchar_t tbuffer[64];

				Engine::Cursor* c = Engine::Cursor::instance();
				//debug code player position
				swprintf_s(tbuffer, 64,L"(%d)",Tower::instance()->getFloor());
				Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

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