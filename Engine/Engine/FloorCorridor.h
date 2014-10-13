#pragma once
#include "Drawable.h"
#include <string>

class FloorCorridor
{
private:
	Drawable info;
	int x, y;
	bool playerOn;
	std::string name;

public:
	FloorCorridor();
	~FloorCorridor();

	virtual void init(std::string handle);
	
	void setScale(D3DXVECTOR3 scale);
	void setTranslate(D3DXVECTOR3 translate);
	void setRotate(D3DXVECTOR3 rotate);

	void setColor(D3DCOLOR color);
	void set3D(bool arg);
	void setHandle(std::string name);

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	bool getOn();
	void setOn(bool arg);

	Drawable getInfo();

	void setName(std::string name);
	std::string getName();

};