#include "Grem.h"


Grem::Grem(void) : Entity()
{
}


Grem::~Grem(void)
{
}

Grem* Grem::instance()
{
	static Grem grem;
	return &grem;
}

void Grem::init()
{
	name = "Grem";

	mesh.init();
	mesh.setScale(1.2f, 1.2f, 1.2f);
	mesh.setHandle("grem");
	mesh.set3D(true);
	mesh.setTranslate(0,0,0);
	mesh.setRotate(mesh.getRotate().x, 270.0f, mesh.getRotate().z );

	rage = 0;
	rageMax = 100;
	xpToLevel = 100;

	Stats temp ={
		//int xp, level, health, maxHealth;
		0,1,30,30,
		//int attack, magic, defense, resist, speed;	
		18,12,12,6,4,
	};
	stats = temp;

	commands[0] = "Fight";
	commands[1] = "NONE";
	commands[2] = "Item";
	commands[3] = "Run";

}

void Grem::levelUp()
{
	if(stats.level < 20){
	stats.level += 1;
	stats.maxHealth += 12;
	stats.health = stats.maxHealth;
	stats.attack += 8;
	stats.magic += 6;
	stats.defense += 6;
	stats.resist += 4;
	stats.speed += 3;
	stats.xp = 0;
	xpToLevel += (float) xpToLevel * 0.3;
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}