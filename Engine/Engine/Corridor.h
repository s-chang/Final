#pragma once

class Corridor
{
private:
	unsigned char icon;
	int x, y;
	bool type;
	
public:
	Corridor();
	~Corridor();

	virtual void init();

	void setIcon(unsigned char icon);
	unsigned char getIcon();

	void setX(int x);
	void setY(int y);
	void setType(bool arg);

	int getX();
	int getY();
	bool getType();



};