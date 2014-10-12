#include "CorridorFactory.h"

CorridorFactory::CorridorFactory()
{}

CorridorFactory::~CorridorFactory()
{}

CorridorFactory *CorridorFactory::instance()
{
	static CorridorFactory factory;
	return &factory;
}

FloorCorridor *CorridorFactory::getCor(std::string handle)
{
	
	if(handle == "cor1U")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor1D")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "cor1R")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor1L")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor2V")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		temp->init("cor2VH");
		return temp;
	}else if(handle == "cor2H")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2VH");
		//temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor2UR")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		temp->init("cor2");
		return temp;
	}else if(handle == "cor2DR")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor2DL")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor2UL")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor3U")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "cor3R")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor3D")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor3L")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor4")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor4");
		return temp;
	}else
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room");
		return temp;
	}
}