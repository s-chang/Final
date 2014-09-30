#include "Laz.h"

Laz::Laz(void) : Entity()
{
}


Laz::~Laz(void)
{
}

Laz* Laz::instance()
{
	static Laz laz;
	return &laz;
}

void Laz::init()
{
	name = "Lazarus";

	mesh.init();
	mesh.setScale(1.2f, 1.2f, 1.2f);
	mesh.setHandle("laz");
	mesh.set3D(true);
	mesh.setTranslate(0,0,0);
	mesh.setRotate(mesh.getRotate().x, 0.0f, mesh.getRotate().z );

	mana = 20;
	manaMax = 20;
	xpToLevel = 100;

	Stats temp ={
		//int xp, level, health, maxHealth;
		0,1,20,20,
		//int attack, magic, defense, resist, speed;	
		9,21,6,14,3,
	};
	stats = temp;

	commands[0] = "Fight";
	commands[1] = "NONE";
	commands[2] = "Item";
	commands[3] = "Run";

}

void Laz::levelUp()
{
	if(stats.level < 20){
	stats.level += 1;
	stats.maxHealth += 8;
	stats.health = stats.maxHealth;
	stats.attack += 4;
	stats.magic += 10;
	stats.defense += 3;
	stats.resist += 7;
	stats.speed += 2;
	stats.xp = 0;
	manaMax += 10;
	mana = manaMax; 
	xpToLevel += (float) xpToLevel * 0.3;
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}
