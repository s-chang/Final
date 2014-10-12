#include "FloorCorridor.h"

FloorCorridor::FloorCorridor()
{}

FloorCorridor::~FloorCorridor()
{}

void FloorCorridor::init(std::string handle)
{
	info.setHandle(handle);
}


void FloorCorridor::setScale(D3DXVECTOR3 scale)
{
	info.setScale(scale.x, scale.y, scale.z);
}

void FloorCorridor::setTranslate(D3DXVECTOR3 translate)
{
	info.setTranslate(translate.x, translate. y, translate.z);
}

void FloorCorridor::setRotate(D3DXVECTOR3 rotate)
{
	info.setRotate(rotate.x, rotate.y, rotate.z);
}

void FloorCorridor::setColor(D3DCOLOR color)
{
	info.setColor(color);
}