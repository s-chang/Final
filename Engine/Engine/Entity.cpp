#include "Entity.h"

Entity::Entity(void)
{
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