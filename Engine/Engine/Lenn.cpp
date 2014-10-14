#include "Lenn.h"
#include "SubtletySkills.h"

Lenn::Lenn(void) : Entity()
{
}


Lenn::~Lenn(void)
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

	/////////////////////////////////////////////////////////////////////////
	// Commands
	/////////////////////////////////////////////////////////////////////////

	BattleCommand* newCommand = new BattleCommand();
	availableCommands.push_back(newCommand);
	newCommand = new Fight();
	availableCommands.push_back(newCommand);
	newCommand = new ItemCMD();
	availableCommands.push_back(newCommand);
	newCommand = new Run();
	availableCommands.push_back(newCommand);
	newCommand = new Subtlety();
	availableCommands.push_back(newCommand);

	commands[0] = availableCommands[1];
	commands[1] = availableCommands[4];
	commands[2] = availableCommands[2];
	commands[3] = availableCommands[3];

	/////////////////////////////////////////////////////////////////////////
	// Skills
	/////////////////////////////////////////////////////////////////////////
	newCommand = new Steal();
	skills.push_back(newCommand);

	/////////////////////////////////////////////////////////////////////////
	// Equipment
	/////////////////////////////////////////////////////////////////////////
	weapon = (Dagger*)ItemFactory::instance()->getItem("Chipped Dagger");
	armor = (Armor*)ItemFactory::instance()->getItem("Clothes");
	acc1 = NULL;
	acc2 = NULL;
	rune1 = NULL;
	rune2 = NULL;

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
	xpToLevel += (int)((float) xpToLevel * 0.3f);
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}

ItemStats* Lenn::getItemStatsForSlot( int slot)
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

Item* Lenn::getItem(int slot)
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

void Lenn::addXP(int amount)
{
	stats.xp += amount;
	if(stats.xp >= xpToLevel)
		levelUp();
};
void Lenn::adjustResource(int amount)
{
	stamina += amount;
	if(stamina <=0 )
		stamina = 0;
	if (stamina >= staminaMax)
		stamina = staminaMax;
};

void Lenn::getSkills(std::vector<BattleCommand*>& skillList, int type)
{
	for(int i = 0; i < skills.size(); i++){
		Skill * skill = (Skill*)skills[i];
		if(skill->getType() == type){
			skillList.push_back(skill);
		}
	}
};

void Lenn::equipItem(Item* item, int slot)
{
	switch(slot)
	{
	case SLOT::WEAPON:
		weapon = (Dagger*)item;	
		break;
	case SLOT::ARMOR:
		armor = (Armor*)item;		
		break;
	case SLOT::ACC1:
		acc1 = (Accessory*)item;		
		break;	
	case SLOT::ACC2:
		acc2 = (Accessory*)item;		
		break;
	case SLOT::RUNE1:
		rune1 = (Rune*)item;		
		break;
	case SLOT::RUNE2:
		rune2 = (Rune*)item;		
		break;
	}
}