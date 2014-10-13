#include "Entity.h"

Entity::Entity(void)
{
	alive = true;
	npc = false;
}

Entity::~Entity(void)
{
}

void Entity::setLevel(int num) 
{
	if(num > 0 && num <=20)
		for(int i = 1; i<num; i++) 
			levelUp();
}
void Entity::adjustHealth(int amount)
{
	stats.health += amount;
	if(stats.health >= stats.maxHealth)
	{
		stats.health = stats.maxHealth;
		alive = true;
	}
	if(stats.health <=0){
		stats.health = 0;
		alive = false;
		mesh.setRotate(90,mesh.getRotate().y,mesh.getRotate().z);
	}
	else{
		alive = true;
		mesh.setRotate(0,mesh.getRotate().y,mesh.getRotate().z);
	}
}
Drawable * Entity::getMesh() 
{ 
	return &mesh; 
}
Stats* Entity::getStats() 
{ 
	return &stats; 
}
std::string Entity::getName() 
{ 
	return name; 
}
bool Entity::isAlive()
{
	return alive;
}
bool Entity::isNPC()
{
	return npc;
}
bool Entity::operator()(Entity* l, Entity* r)
{ 
	return l->getStats()->speed > r->getStats()->speed;
}