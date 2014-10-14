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

FloorRoom *CorridorFactory::getRoom(std::string handle)
{
	if(handle == "room1U")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "room1D")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "room1R")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "room1L")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "room2H")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2vh");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "room2V")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2vh");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "room2UR")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "room2DR")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "room2DL")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "room2UL")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room2");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "room3U")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room3");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "room3R")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room3");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "room3D")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room3");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "room3L")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room3");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "room4")
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room4");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else
	{
		FloorRoom *temp = new FloorRoom();
		temp->init("room4");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}
}

FloorCorridor *CorridorFactory::getCor(std::string handle)
{
	
	if(handle == "cor1U")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor1D")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor1R")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor1L")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor1");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "cor2V")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		temp->init("cor2VH");
		return temp;
	}else if(handle == "cor2H")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2VH");
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		return temp;
	}else if(handle == "cor2UR")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->setRotate(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		temp->init("cor2");
		return temp;
	}else if(handle == "cor2DR")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor2DL")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "cor2UL")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor2");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor3U")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return temp;
	}else if(handle == "cor3R")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f,90.0f, 0.0f));
		return temp;
	}else if(handle == "cor3D")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 180.0f, 0.0f));
		return temp;
	}else if(handle == "cor3L")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor3");
		temp->setRotate(D3DXVECTOR3(0.0f, 270.0f, 0.0f));
		return temp;
	}else if(handle == "cor4")
	{
		FloorCorridor *temp = new FloorCorridor();
		temp->init("cor4");
		return temp;
	}else
	{
		FloorCorridor * temp = new FloorCorridor();
		temp->init("cor1");
		return temp;
	}
}