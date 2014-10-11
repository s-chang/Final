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
	activeCMD = NULL;
	renderNames = true;
	randAI = 0;
	dmg = -1;
	escape = false;
	returnable = 0;

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

	all.push_back(Grem::instance());
	all.push_back(Lenn::instance());
	all.push_back(Laz::instance());

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

	int top = 440;
	int left = 360;
	for(int i = 0; i< 4; i++){
		Grem::instance()->getCommand(i)->setRect(top,left);
		Lenn::instance()->getCommand(i)->setRect(top,left);
		Laz::instance()->getCommand(i)->setRect(top,left);
		top+=35;
	}

	enemies.clear();

	Slime temp;
	struct Pos{
		float x; float z;
	};

	Pos enemyPos[] = {
		{-8.8f,8.8f},
		{-8.8f,2.5f},
		{-2.2f,8.8f},
		{-2.2f,2.5f},
	};

	int num_enemies = rand()%3+2;
	if(num_enemies>4) num_enemies = 4;
	for(int i = 0; i < num_enemies; i++){
		temp.init();
		if(floor > 1){
			int randLevel = rand() %3+(floor-1);
			if (randLevel < 1) randLevel = 1;
			temp.setLevel(randLevel);
		} else 
			temp.setLevel(1);
		d = temp.getMesh();
		d->setTranslate(enemyPos[i].x,0.0f,enemyPos[i].z);
		d->setRotate(0.0f,315.0f,0.0f);

		enemies.push_back(temp);
	}
	for(int i = 0; i < num_enemies; i++){
		all.push_back(&enemies[i]);
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
	//check win/loss
	checkWinLoss();

	renderNames = true;
	if(whosTurn == Turn::PLAYER_TURN){
		if(turnOrder.COUNTER < 3)
			updatePlayerTurn(all[turnOrder.COUNTER]);
		else{
			turnOrder.COUNTER = 0;
			whosTurn = Turn::ENEMY_TURN;
		}
	} 
	else if (whosTurn == Turn::ENEMY_TURN) {
		updateEnemyTurn();
	}
	return returnable;
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

				if(renderNames)
					renderNamesHelthResource();
				//enemies
				RECT rect;
				rect.left = 20;
				rect.top = 450;

				wchar_t tbuffer[64];
				std::string tempString;
				std::wstring tempWS = L"";
				Engine::Text* t = Engine::Text::instance();

				for(auto &enemy: enemies){
					if(enemy.isAlive()){
						tempString = enemy.getName();
						tempWS = std::wstring(tempString.begin(),tempString.end());
						t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

						swprintf_s(tbuffer, 64,L"%d/%d",enemy.getStats()->health,enemy.getStats()->maxHealth);
						rect.left = 100;
						t->font->DrawText(0, tbuffer, -1, &rect, 
							DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					rect.top += 30;
					rect.left = 20;
				}

				if(dmg >=0 && whosTurn == Turn::PLAYER_TURN){
					RECT rect;
					rect.left = Engine::Cursor::instance()->cursorPos.x+120;
					rect.top = Engine::Cursor::instance()->cursorPos.y - 20;
					wchar_t tbuffer[64]; 
					swprintf_s(tbuffer, 64,L"%d",dmg);
					Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &rect, 
						DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
				}

				if(whosTurn == Turn::PLAYER_TURN){
					if(turnOrder.COUNTER < 3)
						renderPlayerTurn(all[turnOrder.COUNTER]);
					else{
						turnOrder.COUNTER = 0;
						whosTurn = Turn::ENEMY_TURN;
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


void Battle::updatePlayerTurn(Entity* e)
{
	if(!e->isAlive()){
		turnOrder.COUNTER++;
		return;
	}
	switch(turnStatus)
	{
	case TURN_STATUS::START:
		for(int i = 0; i<4; i++){
			e->getCommand(i)->checkOn();
			if(Engine::Input::instance()->check_mouse_button(0) 
				&& e->getCommand(i)->isOn())
			{
				activeCMD = e->getCommand(i);
				activeCMD->init();
				turnStatus = TURN_STATUS::CMD;
				break;
			}
		}
		break;
	case TURN_STATUS::CMD:
		activeCMD->update();
		break;
	case TURN_STATUS::END:
		Sleep(1000);
		dmg = -1;
		turnOrder.COUNTER++;
		turnStatus = TURN_STATUS::START;
		break;
	}
}
void Battle::updateEnemyTurn()
{
	if(turnOrder.COUNTER >= turnOrder.ENEMY_COUNT){
		whosTurn = Turn::PLAYER_TURN;
		turnOrder.COUNTER = 0;
		turnStatus = TURN_STATUS::START;
		return;
	}

	Entity * thisGuy = &enemies[turnOrder.COUNTER];
	if(!thisGuy->isAlive()){
		turnOrder.COUNTER++;
		return;
	}
	
	Entity* player = NULL;
	int atk = 0;
	int def = 0;

	switch(turnStatus)
	{
	case TURN_STATUS::START:
		
		randAI = rand()%3;
		player = all[randAI];

		while(!player->isAlive()){
			randAI = rand()%3;
			player = all[randAI];
		}

		atk = thisGuy->getStats()->attack;
		def = player->getStats()->defense + player->getItemStatsForSlot(SLOT::ARMOR)->def;

		dmg = atk - def;
		if(dmg < 0)
			dmg = 0;

		player->adjustHealth(-dmg);
		turnStatus = TURN_STATUS::END;
		break;
	case TURN_STATUS::END:
		Sleep(1000);
		dmg = -1;
		turnOrder.COUNTER++;
		turnStatus = TURN_STATUS::START;
		break;
	}
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

	// command window 
	for(int i=0; i<4; i++){
		BattleCommand* tempCMD = e->getCommand(i);
		tempString = tempCMD->getName();
		if(tempString != "NONE"){
			tempWS = std::wstring(tempString.begin(),tempString.end());
			if(tempCMD->isOn()){
				t->font->DrawText(0, tempWS.c_str(), -1, &tempCMD->getRect(), 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));

				// help text
				rect.left = 50;
				rect.top = 7;
				tempString = tempCMD->helpText();
				tempWS = std::wstring(tempString.begin(),tempString.end());
				t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
					DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
				t->font->DrawText(0, tempWS.c_str(), -1, &tempCMD->getRect(), 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	if(turnStatus == TURN_STATUS::CMD)
		activeCMD->text();
}
void Battle::renderEnemyTurn()
{
	if(turnOrder.COUNTER >= turnOrder.ENEMY_COUNT)
		return;
	Engine::Text* t = Engine::Text::instance();
	Engine::Cursor* c = Engine::Cursor::instance();

	RECT rect;
	rect.left = 50;
	rect.top = 385;

	std::string tempString = enemies[turnOrder.COUNTER].getName();
	std::wstring tempWS = L"";

	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.left = 550;
	wchar_t tbuffer[64]; 
	swprintf_s(tbuffer, 64,L"%d",dmg);

	switch( randAI )
	{
	case 0:
		rect.top = 450;
		t->font->DrawText(0, tbuffer, -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		break;
	case 1:
		rect.top = 495;
		t->font->DrawText(0, tbuffer, -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		break;
	case 2:
		rect.top = 540;
		t->font->DrawText(0, tbuffer, -1, &rect, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		break;
	}
}


void Battle::renderNamesHelthResource()
{
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

	
}

void Battle::BattleOver()
{
	Engine::Text* t = Engine::Text::instance();

	RECT rect;
	rect.left = 20;
	rect.top = 7;
	wchar_t tbuffer[64];
	int totalxp = 0;

	if(turnOrder.COUNTER > 0){
		Sleep(1000);
		returnable = RETURN;
		return;
	}

	switch(whosTurn)
	{
	case Turn::WIN:
		turnOrder.COUNTER++;
		for(auto &enemy: enemies)
			totalxp += enemy.getStats()->xp;
		Grem::instance()->addXP(totalxp);
		Lenn::instance()->addXP(totalxp);
		Laz::instance()->addXP(totalxp);
		swprintf_s(tbuffer, 64,L"You are victorious earning %d XP",totalxp);
		t->font->DrawText(0, tbuffer, -1, &rect, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case Turn::LOSE:
		turnOrder.COUNTER++;
		swprintf_s(tbuffer, 64,L"You've been wrecked",totalxp);
		t->font->DrawText(0, tbuffer, -1, &rect, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case Turn::ESCAPE:
		turnOrder.COUNTER++;
		swprintf_s(tbuffer, 64,L"You Escape...");
		t->font->DrawText(0, tbuffer, -1, &rect, 
				DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void Battle::checkWinLoss()
{
	bool allEnemiesDead = true;
	bool allAlliesDead = true;

	if(Grem::instance()->isAlive())
		allAlliesDead = false;
	if(Lenn::instance()->isAlive())
		allAlliesDead = false;
	if(Laz::instance()->isAlive())
		allAlliesDead = false;

	for(int i = 0; i<turnOrder.ENEMY_COUNT; i++)
		if(enemies[i].isAlive())
			allEnemiesDead = false;

	if(allEnemiesDead)
		whosTurn = Turn::WIN;
	if(allAlliesDead)
		whosTurn = Turn::LOSE;
	if(escape)
		whosTurn = Turn::ESCAPE;
}