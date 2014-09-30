#include "Entity.h"

Entity::Entity(void)
{
	alive = true;
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
bool Entity::operator()(Entity* l, Entity* r)
{ 
	return l->getStats()->speed > r->getStats()->speed;
}