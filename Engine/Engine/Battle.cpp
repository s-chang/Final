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
	int floor = Tower::instance()->getFloor();

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

	Drawable * d;
	Entity* e = Lenn::instance();
	d = e->getMesh();
	d->setTranslate(4.8f,0.0f,0.6f);
	d->setRotate(0.0f,135.0f,0.0f);

	e = Grem::instance();
	d = e->getMesh();
	d->setTranslate(2.4f,0.0f,-1.8f);
	d->setRotate(0.0f,135.0f,0.0f);


	e = Laz::instance();
	d = e->getMesh();
	d->setTranslate(7.7f,0.0f,3.7f);
	d->setRotate(0.0f,135.0f,0.0f);

	Slime temp;
	struct Pos{
		float x; float z;
	};

	Pos enemyPos[] = {
		{-2.2f,8.8f},
		{-8.8f,8.8f},
		{-8.8f,2.5f},
	};

	for(int i = 0; i < 3/*num_enemies*/; i++){
		temp.init();
		int randLevel = rand() %3+(floor-1);
		if (randLevel < 1) randLevel = 1;
		temp.setLevel(randLevel);

		d = temp.getMesh();
		d->setTranslate(enemyPos[i].x,0.0f,enemyPos[i].z);
		d->setRotate(0.0f,315.0f,0.0f);

		enemies.push_back(temp);
	}
	turnOrder.COUNTER = 0;
	turnOrder.ENEMY_COUNT = enemies.size();
	whosTurn = Turn::PLAYER_TURN;
	turnStatus = TURN_STATUS::START;
}

void Battle::shutdown()
{
}

int Battle::update()
{
	if(whosTurn == Turn::PLAYER_TURN){
		switch(turnOrder.COUNTER)
		{
		case 0: // Grem
			Battle::updatePlayerTurn(Grem::instance());
			break;
		case 1: // Lenn
			Battle::updatePlayerTurn(Lenn::instance());
			break;
		case 2: // Laz
			Battle::updatePlayerTurn(Laz::instance());
			break;
		default:
			turnOrder.COUNTER = 0;
			break;
		}
	} 
	else if (whosTurn == Turn::ENEMY_TURN) {
		updateEnemyTurn();
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
			//g->render(player,&cam);
			g->render(*Grem::instance()->getMesh(),&cam);
			g->render(*Lenn::instance()->getMesh(),&cam);
			g->render(*Laz::instance()->getMesh(),&cam);

			for(auto &enemy: enemies){
				if(enemy.isAlive()){
					g->render(*enemy.getMesh(),&cam);
				}
			}

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
				rect.left = 470;
				rect.top = 450;
				wchar_t tbuffer[64];

				// draw names, health, resource
				///////////////////////////////////////////////////////////////////////////////// Grem 
				Grem* grem = Grem::instance();
				std::string tempString = grem->getName();
				std::wstring tempWS = L"";

				tempWS = std::wstring(tempString.begin(),tempString.end());
				t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

				rect.left = 560;
				swprintf_s(tbuffer, 64,L"%d/%d",grem->getStats()->health,grem->getStats()->maxHealth);
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				rect.left = 670;
				swprintf_s(tbuffer, 64,L"%d/%d",grem->getResource(),grem->getMaxResource());
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				///////////////////////////////////////////////////////////////////////////////////
				rect.left = 470;
				rect.top += 45;
				//////////////////////////////////////////////////////////////////////////////////Lenn
				Lenn* lenn = Lenn::instance();
				tempString = lenn->getName();
				//tempWS = L"";

				tempWS = std::wstring(tempString.begin(),tempString.end());
				t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

				rect.left = 560;
				swprintf_s(tbuffer, 64,L"%d/%d",lenn->getStats()->health,lenn->getStats()->maxHealth);
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				rect.left = 670;
				swprintf_s(tbuffer, 64,L"%d/%d",lenn->getResource(),lenn->getMaxResource());
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				//////////////////////////////////////////////////////////////////////////////////////
				rect.left = 470;
				rect.top += 45;
				//////////////////////////////////////////////////////////////////////////////////Laz
				Laz* laz = Laz::instance();
				tempString = laz->getName();
				//tempWS = L"";


				tempWS = std::wstring(tempString.begin(),tempString.end());
				t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

				rect.left = 560;
				swprintf_s(tbuffer, 64,L"%d/%d",laz->getStats()->health,laz->getStats()->maxHealth);
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				rect.left = 670;
				swprintf_s(tbuffer, 64,L"%d/%d",laz->getResource(),laz->getMaxResource());
				t->font->DrawText(0, tbuffer, -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
				//////////////////////////////////////////////////////////////////////////////////////



				if(whosTurn == Turn::PLAYER_TURN){
					switch(turnOrder.COUNTER)
					{
					case 0: // Grem
						Battle::renderPlayerTurn(Grem::instance());
						break;
					case 1: // Lenn
						Battle::renderPlayerTurn(Lenn::instance());
						break;
					case 2: // Laz
						Battle::renderPlayerTurn(Laz::instance());
						break;
					default:
						turnOrder.COUNTER = 0;
						break;
					}
				} 
				else if (whosTurn == Turn::ENEMY_TURN) {
					renderEnemyTurn();
				}
				else {
					BattleOver();
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


void Battle::updatePlayerTurn(Entity* )
{
	switch(turnStatus)
	{
	case TURN_STATUS::START:

		break;
	case TURN_STATUS::OPEN_WINDOW:

		break;
	case TURN_STATUS::SELECTION:

		break;
	case TURN_STATUS::END:

		break;
	}
}
void Battle::updateEnemyTurn()
{

}

void Battle::renderPlayerTurn(Entity* e)
{
	Engine::Text* t = Engine::Text::instance();
	Engine::Cursor* c = Engine::Cursor::instance();

	RECT rect;
	rect.left = 50;
	rect.top = 385;

	std::string tempString = e->getName();
	std::wstring tempWS = L"";

	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.left = 360;
	rect.top = 440;
	
	// command window 
	for(int i=0; i<4; i++){
		tempString = e->getCommand(i);
		if(tempString != "NONE"){
		tempWS = std::wstring(tempString.begin(),tempString.end());
		if(c->cursorPos.x > rect.left+15 && c->cursorPos.x < rect.left + 100
			&& c->cursorPos.y > rect.top+20 && c->cursorPos.y < rect.top + 40 )
			t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
		else
			t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		rect.top += 35;
	}
}
void Battle::renderEnemyTurn()
{
}

void Battle::BattleOver()
{
}