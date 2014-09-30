#include "Lenn.h"

Lenn::Lenn(void) : Entity()
{
}


Lenn::~Lenn(void)
{
}

Lenn* Lenn::instance()
{
	static Lenn tower;
	return &tower;
}

void Lenn::init()
{
	name = "Lenn";

	mesh.init();
	mesh.setScale(1.2f, 1.2f, 1.2f);
	mesh.setHandle("lenn");
	mesh.set3D(true);
	mesh.setTranslate(0,0,0);
	mesh.setRotate(mesh.getRotate().x, 0.0f, mesh.getRotate().z );

	stamina = 0;
	staminaMax = 100;
	xpToLevel = 100;

	Stats temp ={
		//int xp, level, health, maxHealth;
		0,1,25,25,
		//int attack, magic, defense, resist, speed;	
		12,15,8,10,6,
	};
	stats = temp;

	commands[0] = "Fight";
	commands[1] = "NONE";
	commands[2] = "Item";
	commands[3] = "Run";

}

void Lenn::levelUp()
{
	if(stats.level < 20){
	stats.level += 1;
	stats.maxHealth += 10;
	stats.health = stats.maxHealth;
	stats.attack += 6;
	stats.magic += 7;
	stats.defense +=4;
	stats.resist +=5;
	stats.speed += 4;
	stats.xp = 0;
	xpToLevel += (float) xpToLevel * 0.3;
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}


