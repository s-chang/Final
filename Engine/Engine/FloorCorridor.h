#pragma once
#include "Drawable.h"
#include <string>

class FloorCorridor
{
private:
	Drawable info;

public:
	FloorCorridor();
	~FloorCorridor();

	void init(std::string handle);
	
	void setScale(D3DXVECTOR3 scale);
	void setTranslate(D3DXVECTOR3 translate);
	void setRotate(D3DXVECTOR3 rotate);

	void setColor(D3DCOLOR color);

};