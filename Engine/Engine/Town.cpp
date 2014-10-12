#include "Town.h"


Town::Town(void) : GameState()
{
}

Town* Town::instance()
{
	static Town t;
	return &t;
}

Town::~Town(void)
{
}

void Town::init()
{
	player.init();
	player.setScale(1.0f, 1.0f, 1.0f);
	player.setHandle("grem");
	player.set3D(true);
	player.setTranslate(-37.0f,0.0f,-7.7f);
	player.setRotate(player.getRotate().x, 270.0f, player.getRotate().z );

	town.init();
	town.setScale(7.0f, 7.0f, 7.0f);
	town.setRotate(0,90,0);
	town.setHandle("town");
	town.set3D(true);

	helpBar.init();
	helpBar.setScale(.77f, 1.0f, 1.0f);
	helpBar.setHandle("helpBar");
	helpBar.setTranslate(303,50,0);

	mBox.init();
	mBox.setScale(1.0f, 1.0f, 1.0f);
	mBox.setHandle("mBox");
	mBox.setTranslate(600,300,0);

	cam.init(800,600);
	cam.setEyePos(-42.0f,10.0f,-22.7f);
	cam.setLookAt(player.getTranslate().x, -3.75f, player.getTranslate().z);
	cam.setProj();

	//Engine::Graphics::instance()->init(&cam,&light);
	goToFloor = 1;
	tutorial = true;
}

void Town::shutdown()
{
}

int Town::update()
{

	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor* c = Engine::Cursor::instance();

	if(input->push_button(DIK_W))
	{		
		int _x = (int)player.getTranslate().x;

		if (_x > -32 && _x < -26){ //INN 
			return INN;
		}
		else if (_x > -5 && _x < 1){ //Shop
			return SHOP;
		} 
		else if (_x > 23 && _x < 29){ //Tavern 
			return TAVERN;
		}
	}

	if(input->push_button(DIK_A))
	{
		player.setTranslate(player.getTranslate().x - 0.1f , 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 90.0f, player.getRotate().z );
		if(player.getTranslate().x < -40)
			player.setTranslate(-40.0f,0.0f,-7.7f);
		else 
			cam.setEyePos(cam.getEyePos().x - 0.1f, cam.getEyePos().y, cam.getEyePos().z );
	}

	if(input->push_button(DIK_D))
	{
		player.setTranslate(player.getTranslate().x + 0.1f, 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 270.0f, player.getRotate().z );
		if(player.getTranslate().x > 49)
			player.setTranslate(49.0f,0.0f,-7.7f);
		else
			cam.setEyePos(cam.getEyePos().x + 0.1f, cam.getEyePos().y, cam.getEyePos().z );

	}
	cam.setEyePos(cam.getEyePos().x, 10.0f, cam.getEyePos().z);
	cam.setLookAt(player.getTranslate().x, 5.0f, player.getTranslate().z);
	cam.setProj();

	if(input->check_mouse_button(0)){
		if(player.getTranslate().x > 48){
			// test case first floor
			if(c->cursorPos.x > 551 && c->cursorPos.x <650
				&& c->cursorPos.y > 347 && c->cursorPos.y < 367){
					goToFloor = 1;
					return TOWER;
			}
			if(c->cursorPos.x > 551 && c->cursorPos.x <650
				&& c->cursorPos.y > 390 && c->cursorPos.y < 410
				/*&& player.clearedFifth()*/){
					goToFloor = 5;
					return TOWER;
			}
			if(c->cursorPos.x > 551 && c->cursorPos.x <660
				&& c->cursorPos.y > 427 && c->cursorPos.y < 447
				/*&& player.clearedTenth()*/){
					goToFloor = 10;
					return TOWER;
			}
		}
	}

	if(input->push_button(DIK_G)){
		if(!input->check_button_down(DIK_G)){
			input->set_button(DIK_G,true);
			return STATUSMENU;
		}
	} else input->set_button(DIK_G,false);


	///////////////////////////////////////////////
	// debug instaswitch to battle
	///////////////////////////////////////////////
	if(input->push_button(DIK_B))
		return BATTLE;

	return 0;
}
void Town::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	Engine::Graphics* g = Engine::Graphics::instance();

	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{
			/////////////////////////////////////////
			// 3D objects
			/////////////////////////////////////////
			g->render(player,&cam);
			g->render(town,&cam);

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				/////////////////////////////////////////
				// 2D objects
				/////////////////////////////////////////
				int _x = (int)player.getTranslate().x;
				//if(     _x < -39 //end of town
				//	|| (_x > -32 && _x < -28)//INN 
				//	|| (_x > -3 && _x < 1)//Shop 
				//	|| (_x > 25 && _x < 29)//Tavern 
				//	)
				g->Draw2DObject(helpBar);
				if(player.getTranslate().x > 48)
					g->Draw2DObject(mBox);
				Engine::DX::instance()->getSprite()->End();

				////////////////////////////////////////
				//text
				////////////////////////////////////////

				Engine::Text* t = Engine::Text::instance();

				RECT rect;
				rect.left = 200;
				rect.top = 200;
				//wchar_t tbuffer[64];

				Engine::Cursor* c = Engine::Cursor::instance();
				//debug code player position
				/*swprintf_s(tbuffer, 64,L"(%f,%f)",c->cursorPos.x,c->cursorPos.y);
				Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));*/

				rect.left = 20;
				rect.top = 45;
				// help text
				if(_x < -39 ){ //end of town
					t->font->DrawText(0, L"Cannot Leave Town", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else if (_x > -32 && _x < -26){ //INN 
					t->font->DrawText(0, L"Press W to Enter INN", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else if (_x > -5 && _x < 1){ //Shop
					t->font->DrawText(0, L"Press W to Enter Shop", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				} 
				else if (_x > 23 && _x < 29){ //Tavern 
					t->font->DrawText(0, L"Press W to Enter Tavern", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else {
					t->font->DrawText(0, L"Press A and D to move Left and Right", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				// Enter Tower/Floor Selection
				if(player.getTranslate().x > 48){
					rect.left = 500;
					rect.top = 230;
					t->font->DrawText(0, L"Are You Prepared To", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					rect.top += 30;
					t->font->DrawText(0, L"Enter The Tower?", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					rect.top += 30;
					t->font->DrawText(0, L"   Select Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

					rect.top += 40;
					if(c->cursorPos.x > 551 && c->cursorPos.x <650
						&& c->cursorPos.y > 347 && c->cursorPos.y < 367)
						t->font->DrawText(0, L"      First Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
					else
						t->font->DrawText(0, L"      First Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					//if(player.clearedFifth()){
					rect.top += 40;
					if(c->cursorPos.x > 551 && c->cursorPos.x <650
						&& c->cursorPos.y > 390 && c->cursorPos.y < 410)
						t->font->DrawText(0, L"      Fifth Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
					else
						t->font->DrawText(0, L"      Fifth Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					//}
					//if(player.clearedTenth()){
					rect.top += 40;
					if(c->cursorPos.x > 551 && c->cursorPos.x <660
						&& c->cursorPos.y > 427 && c->cursorPos.y < 447)
						t->font->DrawText(0, L"      Tenth Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
					else
						t->font->DrawText(0, L"      Tenth Floor", -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					//}

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