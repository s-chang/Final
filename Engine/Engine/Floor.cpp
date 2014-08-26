#include "Floor.h"
#include <fstream>
#include "Input.h"

Floor::Floor()
{
	rooms.clear();
	corridor.clear();
	enemies.clear();
	treasure.clear();
	
}

Floor::~Floor()
{}


void Floor::init()
{
	player.init();
	player.setScale(1.0f, 1.0f, 1.0f);
	player.setHandle("grem");
	player.set3D(true);
	//player.setHasTexture(false);

	stair.init();
	stair.setScale(1.0f, 1.0f, 1.0f);
	stair.setHandle("skybox");
	stair.set3D(true);
	stair.setHasTexture(false);
	

	roomMain.init();
	roomMain.setScale(2.0f, 2.0f, 2.0f);
	roomMain.setHandle("4room");
	roomMain.set3D(true);

	roomSide1.init();
	roomSide1.setScale(2.0f, 2.0f, 2.0f);
	roomSide1.setRotate(0.0, 0.0f, 0.0f);
	roomSide1.setTranslate(0.0f, 0.0f, 20.75f);
	roomSide1.set3D(true);
	roomSide1.setHandle("1room");

	roomSide2.init();
	roomSide2.setScale(2.0f, 2.0f, 2.0f);
	roomSide2.setRotate(0.0, 90.0f, 0.0f);
	roomSide2.setTranslate(20.75f, 0.0f, 0.0f);
	roomSide2.set3D(true);
	roomSide2.setHandle("1room");

	roomSide3.init();
	roomSide3.setScale(2.0f, 2.0f, 2.0f);
	roomSide3.setRotate(0.0, 180.0f, 0.0f);
	roomSide3.setTranslate(0.0f, 0.0f, -20.75f);
	roomSide3.set3D(true);
	roomSide3.setHandle("1room");

	roomSide4.init();
	roomSide4.setScale(2.0f, 2.0f, 2.0f);
	roomSide4.setRotate(0.0, 270.0f, 0.0f);
	roomSide4.setTranslate(-20.75f, 0.0f, 0.0f);
	roomSide4.set3D(true);
	roomSide4.setHandle("1room");

	light.defaultInit();
	light.setLight();

	floorCam.init(800,600);
	//floorCam.setLookAt(player.getTranslate().x, 0.0f, player.getTranslate().z);
	//floorCam.setLookAt(0.0f, 0.0f, 0.0f);
	floorCam.setLookAt(player.getTranslate().x, -3.75f, player.getTranslate().z);
	floorCam.setProj();
}

void Floor::loadDefaultFloor()
{
	std::ifstream file("DMap.txt");
	int id;
	
		for(int i = 0; i < msize; i++)
		{
			for(int j = 0; j < msize; j++)
			{
				id = file.get();
				if(id == '\n' || id == '\r')
				{
					j--;
					continue;
				}
				map[i][j] = id;
			}
		}
	file.close();




}

void Floor::update()
{
	

	if(Engine::Input::instance()->push_button(DIK_W))
	{		
		player.setTranslate(player.getTranslate().x , 0.0f, player.getTranslate().z + 0.1f);
		player.setRotate(player.getRotate().x, 180.0f, player.getRotate().z );
		floorCam.setEyePos(floorCam.getEyePos().x, floorCam.getEyePos().y, floorCam.getEyePos().z + 0.1f);

	}

	if(Engine::Input::instance()->push_button(DIK_S))
	{
		player.setTranslate(player.getTranslate().x , 0.0f, player.getTranslate().z - 0.1f);
		player.setRotate(player.getRotate().x, 0.0f, player.getRotate().z );
		floorCam.setEyePos(floorCam.getEyePos().x, floorCam.getEyePos().y, floorCam.getEyePos().z - 0.1f);
	}

	if(Engine::Input::instance()->push_button(DIK_A))
	{
		player.setTranslate(player.getTranslate().x - 0.1f , 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 90.0f, player.getRotate().z );
		floorCam.setEyePos(floorCam.getEyePos().x - 0.1f, floorCam.getEyePos().y, floorCam.getEyePos().z );
	}

	if(Engine::Input::instance()->push_button(DIK_D))
	{
		player.setTranslate(player.getTranslate().x + 0.1f, 0.0f, player.getTranslate().z );
		player.setRotate(player.getRotate().x, 270.0f, player.getRotate().z );
		floorCam.setEyePos(floorCam.getEyePos().x + 0.1f, floorCam.getEyePos().y, floorCam.getEyePos().z );
	}
	floorCam.setEyePos(floorCam.getEyePos().x, 10.0f, floorCam.getEyePos().z);
	floorCam.setLookAt(player.getTranslate().x, 5.0f, player.getTranslate().z);
	floorCam.setProj();



	for(unsigned int i = 0; i < rooms.size(); i++)
		drawQ.push(rooms[i]);
	for(unsigned int i = 0; i < corridor.size(); i++)
		drawQ.push(corridor[i]);
	for(unsigned int i = 0; i < enemies.size(); i++)
		drawQ.push(enemies[i]);
	for(unsigned int i = 0; i < treasure.size(); i++)
		drawQ.push(treasure[i]);	
	//drawQ.push(stair);

	drawQ.push(roomMain);
	drawQ.push(roomSide1);
	drawQ.push(roomSide2);
	drawQ.push(roomSide3);
	drawQ.push(roomSide4);
	drawQ.push(player);
}

std::queue<Drawable> *Floor::getDrawQ()
{
	return &drawQ;
}

Camera *Floor::getCamera()
{
	return &floorCam;
}