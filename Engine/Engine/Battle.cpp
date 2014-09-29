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
	bWindow.init();
	bWindow.setScale(0.788f, 0.59f, 1.0f);
	bWindow.setHandle("bWindow");
	bWindow.setTranslate(310,175,0);

	platform.init();
	platform.setScale(3.0f, 3.0f, 3.0f);
	platform.setHandle("bPlat");
	platform.set3D(true);
	platform.setTranslate(0,0,0);
	platform.setRotate(0,45,0);

	cam.init(800,600);
	cam.setEyePos(0,13,-13);
	cam.setLookAt(0,0,0);
	cam.setProj();

	player.init();
	player.setScale(1.0f, 1.0f, 1.0f);
	player.setHandle("lenn");
	player.set3D(true);
	player.setTranslate(0,0,0);
	player.setRotate(player.getRotate().x, 270.0f, player.getRotate().z );
}

void Battle::shutdown()
{
}

int Battle::update()
{
	Engine::Input* input = Engine::Input::instance();

	if(input->push_button(DIK_W)){		
		player.setTranslate(player.getTranslate().x , 0.0f, player.getTranslate().z + 0.1f);
		player.setRotate(player.getRotate().x, 180.0f, player.getRotate().z );

	}

	if(input->push_button(DIK_S)){
		player.setTranslate(player.getTranslate().x , 0.0f, player.getTranslate().z - 0.1f);
		player.setRotate(player.getRotate().x, 0.0f, player.getRotate().z );
	}

	if(input->push_button(DIK_A)){
		player.setTranslate(player.getTranslate().x - 0.1f , 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 90.0f, player.getRotate().z );
	}

	if(input->push_button(DIK_D)){
		player.setTranslate(player.getTranslate().x + 0.1f, 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 270.0f, player.getRotate().z );

	}

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
			g->render(platform,&cam);
			g->render(player,&cam);

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				/////////////////////////////////////////
				// 2D objects
				/////////////////////////////////////////

				g->Draw2DObject(bWindow);

				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////

				Engine::Text* t = Engine::Text::instance();

				RECT rect;
				rect.left = 100;
				rect.top = 50;
				wchar_t tbuffer[64];



				//debug code player position
				swprintf_s(tbuffer, 64,L"(%f,%f)",player.getTranslate().x,player.getTranslate().z);
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