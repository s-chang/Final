#include "Grem.h"
#include "Skill.h"

Grem::Grem(void) : Entity()
{
}


Grem::~Grem(void)
{
	while(!availableCommands.empty()){
		delete availableCommands.back();
		availableCommands.pop_back();
	}
	delete weapon;
	delete armor;
	delete acc1;
	delete acc2;
	delete rune1;
	delete rune2;
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
		18,12,8,6,4,
	};
	stats = temp;

	BattleCommand* newCommand = new BattleCommand();
	availableCommands.push_back(newCommand);
	newCommand = new Fight();
	availableCommands.push_back(newCommand);
	newCommand = new ItemCMD();
	availableCommands.push_back(newCommand);
	newCommand = new Run();
	availableCommands.push_back(newCommand);
	newCommand = new RageCMD();
	availableCommands.push_back(newCommand);

	commands[0] = availableCommands[1];
	commands[1] = availableCommands[4];
	commands[2] = availableCommands[2];
	commands[3] = availableCommands[3];

	weapon = (Spear*)ItemFactory::instance()->getItem("Weathered Spear");
	armor = (Armor*)ItemFactory::instance()->getItem("Clothes");

	acc1 = NULL;
	acc2 = NULL;
	rune1 = NULL;
	rune2 = NULL;

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
	xpToLevel += (int)((float) xpToLevel * 0.3f);
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}

ItemStats* Grem::getItemStatsForSlot( int slot)
{
	switch(slot)
	{
	case SLOT::WEAPON:
		return &weapon->getStats();
	case SLOT::ARMOR:
		return &armor->getStats();
	case SLOT::ACC1:
		return &acc1->getStats();
	case SLOT::ACC2:
		return &acc2->getStats();
	case SLOT::RUNE1:
		return &rune1->getStats();
	case SLOT::RUNE2:
		return &rune2->getStats();
	}
}
Item* Grem::getItem(int slot)
{
	switch(slot)
	{
	case SLOT::WEAPON:
		if(weapon)	return weapon;
		else		return NULL;
	case SLOT::ARMOR:
		if(armor)	return armor;
		else		return NULL;
	case SLOT::ACC1:
		if(acc1)	return acc1;
		else		return NULL;
	case SLOT::ACC2:
		if(acc2)	return acc2;
		else		return NULL;
	case SLOT::RUNE1:
		if(rune1)	return rune1;
		else		return NULL;
	case SLOT::RUNE2:
		if(rune2)	return rune2;
		else		return NULL;
	}
}
void Grem::addXP(int amount)
{
	stats.xp += amount;
	if(stats.xp >= xpToLevel)
		levelUp();
};
void Grem::adjustResource(int amount)
{
	rage += amount;
	if(rage <=0 )
		rage = 0;
	if (rage >= rageMax)
		rage = rageMax;
};

void Grem::getSkills(std::vector<BattleCommand*>& skillList, int type)
{
	for(int i = 0; i < skills.size(); i++){
		Skill * skill = (Skill*)skills[i];
		if(skill->getType() == type){
			skillList.push_back(skill);
		}
	}
};