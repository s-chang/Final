#include "Slime.h"


Slime::Slime(void) : Entity()
{
}


Slime::~Slime(void)
{
}

void Slime::init()
{
	name = "Slime";

	mesh.init();
	mesh.setScale(1.0f, 1.0f, 1.0f);
	mesh.setHandle("slime");
	mesh.set3D(true);
	mesh.setTranslate(0,0,0);
	mesh.setRotate(0.0f, 0.0f,0.0f );

	Stats temp ={
		//int xp given upon death, level, health, maxHealth;
		10,1,35,35,
		//int attack, magic, defense, resist, speed;	
		15, 15, 10, 10, 5,
	};
	stats = temp;

}

void Slime::levelUp()
{
	if(stats.level < 20){
		stats.level += 1;
		stats.maxHealth += 10;
		stats.health = stats.maxHealth;
		stats.attack += 6;
		stats.magic += 7;
		stats.defense += 4;
		stats.resist += 5;
		stats.speed += 3;
		stats.xp = 0;
	}

}
