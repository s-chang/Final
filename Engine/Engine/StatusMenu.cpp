#include "StatusMenu.h"
#include "Graphics.h"
#include "Text.h"

StatusMenu::StatusMenu()
{}

StatusMenu::~StatusMenu()
{}

StatusMenu *StatusMenu::instance()
{
	static StatusMenu menu;
	return &menu;

}

void StatusMenu::init()
{
	status_state = STAT_MAIN;


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
	temp.setTranslate(80.0f, 295.0f, 0.0f);
	portraits.push_back(temp);

	temp.setHandle("lazPortrait");
	temp.setTranslate(80.0f, 470.0f, 0.0f);
	portraits.push_back(temp);

	//Init character names and location
	Drawable tempNames;
	tempNames.init();
	tempNames.setTranslate(180.0f, 105.0f, 0.0f);
	tempNames.setText(L"Grem");

	names.push_back(tempNames);

	tempNames.setTranslate(180.0f, 285.0f, 0.0f);
	tempNames.setText(L"Lenn");
	names.push_back(tempNames);

	tempNames.setTranslate(180.0f, 465.0f, 0.0f);
	tempNames.setText(L"Lazarus");
	names.push_back(tempNames);

	//Init character HP, resource, and location


	//Init gold, playtime, and location

	//init status commands
	//100x50
	Drawable tempCommands;
	RECT tempR;
	tempCommands.setTranslate(700.0f, 95.0f,0.0f);
	tempR.left = 650;
	tempR.right = 800;
	tempR.top = 70;
	tempR.bottom = 120;
	tempCommands.init();
	tempCommands.setText(L"Inventory");
	tempCommands.setRect(tempR);
	status_commands.push_back(tempCommands);

	



}

void StatusMenu::shutdown()
{

}

int StatusMenu::update()
{

	switch(status_state)
	{
	case STAT_MAIN:
		{
			for(unsigned int i = 0; i < status_commands.size(); i++)
			{
				if(status_commands[i].checkOn(Engine::Cursor::instance()->cursorPos.x,
					Engine::Cursor::instance()->cursorPos.y, 3))
				{
					status_commands[i].setColor(D3DCOLOR_ARGB(255,255,255,0));
					//check for mouse click 
					if(Engine::Input::instance()->check_mouse_button(LEFT_MOUSE_BUTTON))
					{
						if(!Engine::Input::instance()->check_button_down(DIK_9))
						{
							Engine::Input::instance()->set_button(DIK_9, true);

							switch(i+1)
							{
							case ITEM:
								status_state = ITEM;
								break;
							case EQUIP:
								status_state = EQUIP;
								break;
							case SKILLS:
								status_state = SKILLS;
								break;
							case STATUS:
								status_state = STATUS;
								break;
							case STAT_OPTIONS:
								status_state = STAT_OPTIONS;
								break;
							case BACK:
								status_state = STAT_MAIN;
								return RETURN;
								break;
							}
						}//end if
						
					}//end if
					else
						Engine::Input::instance()->set_button(DIK_9, false);
				}//end if
				else
					status_commands[i].setColor(D3DCOLOR_ARGB(255,255,255,255));
			}//end for loop


		}//end STAT_MAIN
		break;
	case ITEM:
	case EQUIP:
	case SKILLS:
	case STATUS:
	case STAT_OPTIONS:
	}
	return 0;
}

void StatusMenu::render()
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

				Engine::Graphics::instance()->drawCursor();

				
				Engine::DX::instance()->getSprite()->End();
			}//End Begin


				//Draw Text
			for(int i = 0; i < MAX_CHARACTERS; i++)
			{
				Engine::Text::instance()->render((long)names[i].getTranslate().y, (long)names[i].getTranslate().x, names[i].getPlainText(), names[i].getColor());
			}

			//Draw Status Commands
			for(unsigned int i = 0; i < status_commands.size(); i++)
			{
				Engine::Text::instance()->render(status_commands[i].getRect().top, status_commands[i].getRect().left, status_commands[i].getPlainText(), status_commands[i].getColor());
			}
		

		}//End BeginScene
		Engine::DX::instance()->getDevice()->EndScene();
	}//end clear
	Engine::DX::instance()->getDevice()->Present(0,0,0,0);
}

void StatusMenu::setMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world, Drawable &object)
{
		D3DXMatrixScaling(&scale, object.getScale().x, object.getScale().y, object.getScale().z);
		D3DXMatrixTranslation(&translate, object.getTranslate().x, object.getTranslate().y, object.getTranslate().z);
		D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(object.getRotate().y),D3DXToRadian(object.getRotate().x), D3DXToRadian(object.getRotate().z));
		D3DXMatrixMultiply(&scale, &scale, &rotate);
		D3DXMatrixMultiply(&world, &scale, &translate);

		Engine::DX::instance()->getSprite()->SetTransform(&world);

}

void StatusMenu::resetMatrices(D3DXMATRIX &translate, D3DXMATRIX &scale, D3DXMATRIX &rotate, D3DXMATRIX &world)
{
	D3DXMatrixIdentity(&translate);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotate);
	D3DXMatrixIdentity(&world);
}