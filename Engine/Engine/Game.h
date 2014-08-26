#pragma once

#include "TestObj.h"
#include <queue>
#include "Camera.h"
#include "Floor.h"

enum{
TITLE,
TOWERFLOOR,


};


class Game
{
private:
	//std::queue<Drawable> drawQ;

	//TODO: create a better storage for text
	/*struct TextData
	{
		wchar_t *wordbuffer;
		int top;
		int left;
		D3DCOLOR color;
	};

	std::queue<TextData> textQ;*/


	//TestObj mesh1;

	int game_state;

	//Camera tempCam;

	Floor floor;
	std::queue<Drawable>* drawQ;
	void reset();

	Camera *cam;

	MSG msg;
	
public:
	Game();
	~Game();

	void init();

	void update(MSG &msg);
	void render();

	void shutdown();
};