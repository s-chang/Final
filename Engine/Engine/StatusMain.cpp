#include "StatusMain.h"
#include "Player.h"

StatusMain::StatusMain(void)
{
}


StatusMain::~StatusMain(void)
{
}

StatusMain* StatusMain::instance()
{
	static StatusMain menu;
	return &menu;
}
void StatusMain::init()
{
	//Init background image
	background.init();
	background.setHandle("statusMain");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	//Init portrait handles and location
	Drawable temp;
	temp.init();
	temp.setHandle("gremPortrait");
	temp.setTranslate(80.0f, 115.0f, 0.0f);
	portraits.push_back(temp);

	temp.setHandle("lennPortrait");
	temp.setTranslate(80.0f, 293.0f, 0.0f);
	portraits.push_back(temp);

	temp.setHandle("lazPortrait");
	temp.setTranslate(80.0f, 470.0f, 0.0f);
	portraits.push_back(temp);

	////Init character names and location
	//Drawable tempNames;
	//tempNames.init();
	//tempNames.setTranslate(180.0f, 105.0f, 0.0f);
	//tempNames.setText(L"Grem");

	//names.push_back(tempNames);

	//tempNames.setTranslate(180.0f, 285.0f, 0.0f);
	//tempNames.setText(L"Lenn");
	//names.push_back(tempNames);

	//tempNames.setTranslate(180.0f, 465.0f, 0.0f);
	//tempNames.setText(L"Lazarus");
	//names.push_back(tempNames);

	//Init character HP, resource, and location


	//Init gold, playtime, and location

	//init status commands
	//100x50
	// status command data
	

	SCDATA scdata[] = {
		{700.0f, 95.0f,70,650,120,800,L"Inventory"}, //0 inve
		{700.0f, 145.0f,120,650,170,800,L"Equip"},
		{700.0f, 195.0f,170,650,220,800,L"Skills"},
		{700.0f, 245.0f,220,650,270,800,L"Status"},
		{700.0f, 295.0f,270,650,320,800,L"Options"},
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
		status_commands.push_back(tempCommands);
	}
}

void StatusMain::shutdown()
{

}

int StatusMain::update()
{
	for(unsigned int i = 0; i < status_commands.size(); i++)
	{
		if(status_commands[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
			Engine::Cursor::instance()->cursorPos.y, 3))
		{
			status_commands[i].setColor(D3DCOLOR_ARGB(255,255,255,0));

			if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON))
			{
				if(!Engine::Input::instance()->check_button_down(DIK_9))
				{
					Engine::Input::instance()->set_button(DIK_9, true);

					switch(i)
					{
					case 0: //inventory
						return STATUS_STATE::INVENTORY;
					case 1: //equip
						return STATUS_STATE::EQUIP;
					case 2: //skills
						return STATUS_STATE::SKILLS;
					case 3: //status
						return STATUS_STATE::STATUS;
					case 4: //Options
						return STATUS_STATE::OPTIONS;
					}
				}

			}
			else Engine::Input::instance()->set_button(DIK_9, false);
		}
		else
			status_commands[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
	}

	return 0;
}

void StatusMain::render()
{
	if(!Engine::DX::instance()->getDevice())
		return;

	if(SUCCEEDED(Engine::DX::instance()->getDevice()->Clear(0,0,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0)))
	{
		if(SUCCEEDED(Engine::DX::instance()->getDevice()->BeginScene()))
		{


			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			{
				D3DXMATRIX transMat, scaleMat, rotMat, worldMat;

				resetMatrices(transMat, scaleMat, rotMat, worldMat);
				//Render the background
				setMatrices(transMat, scaleMat, rotMat, worldMat, background);

				Engine::DX::instance()->getSprite()->Draw(
					Engine::Graphics::instance()->getTexture(background.getHandle()),
					0, 
					&D3DXVECTOR3(Engine::Graphics::instance()->getInfo(background.getHandle()).Width * 0.5f,
					Engine::Graphics::instance()->getInfo(background.getHandle()).Height * 0.5f, 0.0f),
					0, 
					background.getColor());


				//Portraits
				for(int i = 0; i < MAX_CHARACTERS; i++)
				{
					resetMatrices(transMat, scaleMat, rotMat, worldMat);
					setMatrices(transMat, scaleMat, rotMat, worldMat, portraits[i]);

					Engine::DX::instance()->getSprite()->Draw(
						Engine::Graphics::instance()->getTexture(portraits[i].getHandle()),
						0, 
						&D3DXVECTOR3(Engine::Graphics::instance()->getInfo(portraits[i].getHandle()).Width * 0.5f,
						Engine::Graphics::instance()->getInfo(portraits[i].getHandle()).Height * 0.5f, 0.0f),
						0, 
						portraits[i].getColor());

				}


				Engine::DX::instance()->getSprite()->End();
			}//End Begin


			//Draw Text
			/*for(int i = 0; i < MAX_CHARACTERS; i++)
			{
				Engine::Text::instance()->render((long)names[i].getTranslate().y, (long)names[i].getTranslate().x, names[i].getPlainText(), names[i].getColor());
			}*/

			renderNamesAndStats();

			//Draw Status Commands
			for(unsigned int i = 0; i < status_commands.size(); i++)
			{
				Engine::Text::instance()->render(status_commands[i].getRect().top, status_commands[i].getRect().left, status_commands[i].getPlainText(), status_commands[i].getColor());
			}

			

			//////////////////////////////////////////////
			// Cursor
			//////////////////////////////////////////////

			if(SUCCEEDED(Engine::DX::instance()->getSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK))){
				Engine::Graphics::instance()->drawCursor();
				Engine::DX::instance()->getSprite()->End();
			}

		}//End BeginScene
		Engine::DX::instance()->getDevice()->EndScene();
	}//end clear
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}


void StatusMain::setMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world, Drawable &object)
{
	D3DXMatrixScaling(&scale, object.getScale().x, object.getScale().y, object.getScale().z);
	D3DXMatrixTranslation(&translate, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
	D3DXMatrixMultiply(&scale, &scale, &rotate);
	D3DXMatrixMultiply(&world, &scale, &translate);

	Engine::DX::instance()->getSprite()->SetTransform(&world);

}

void StatusMain::resetMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world)
{
	D3DXMatrixIdentity(&translate);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotate);
	D3DXMatrixIdentity(&world);
}

void StatusMain::renderNamesAndStats()
{
	Engine::Text* t = Engine::Text::instance();

	RECT rect;
	rect.top = 70;
	rect.left = 170;
	wchar_t tbuffer[64];

	// draw names, health, resource
	///////////////////////////////////////////////////////////////////////////////// Grem 
	Grem* grem = Grem::instance();
	std::string tempString = grem->getName();
	std::wstring tempWS = L"";

	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top += 40;
	rect.left += 30;
	swprintf_s(tbuffer, 64,L"Level %d",grem->getStats()->level);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top -= 10;
	rect.left += 120;
	swprintf_s(tbuffer, 64,L"Health %d/%d",grem->getStats()->health,grem->getStats()->maxHealth);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top += 40;
	swprintf_s(tbuffer, 64,L"Rage %d/%d",grem->getResource(),grem->getMaxResource());
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	///////////////////////////////////////////////////////////////////////////////////
	rect.top = 250;
	rect.left = 170;
	//////////////////////////////////////////////////////////////////////////////////Lenn
	Lenn* lenn = Lenn::instance();
	tempString = lenn->getName();
	//tempWS = L"";

	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top += 40;
	rect.left += 30;
	swprintf_s(tbuffer, 64,L"Level %d",lenn->getStats()->level);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top -= 10;
	rect.left += 120;
	swprintf_s(tbuffer, 64,L"Health %d/%d",lenn->getStats()->health,lenn->getStats()->maxHealth);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top += 40;
	swprintf_s(tbuffer, 64,L"Stamina %d/%d",lenn->getResource(),lenn->getMaxResource());
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	//////////////////////////////////////////////////////////////////////////////////////
	rect.top = 430;
	rect.left = 170;
	//////////////////////////////////////////////////////////////////////////////////Laz
	Laz* laz = Laz::instance();
	tempString = laz->getName();
	//tempWS = L"";


	tempWS = std::wstring(tempString.begin(),tempString.end());
	t->font->DrawText(0, tempWS.c_str(), -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top += 40;
	rect.left += 30;
	swprintf_s(tbuffer, 64,L"Level %d",laz->getStats()->level);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	rect.top -= 10;
	rect.left += 120;
	swprintf_s(tbuffer, 64,L"Health %d/%d",laz->getStats()->health,laz->getStats()->maxHealth);
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	rect.top += 40;
	swprintf_s(tbuffer, 64,L"Mana %d/%d",laz->getResource(),laz->getMaxResource());
	t->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	//////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////
	// Gold
	//////////////////////////////////////////////////////////////////////////////////////
	rect.left = 650;
	rect.top = 355;
	swprintf_s(tbuffer, 64,L"Gold \n   %d",Player::instance()->getGold());
	Engine::Text::instance()->font->DrawText(0, tbuffer, -1, &rect, 
		DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}