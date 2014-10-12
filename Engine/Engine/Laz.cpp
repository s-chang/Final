#include "Laz.h"
#include "Skill.h"

Laz::Laz(void) : Entity()
{
}


Laz::~Laz(void)
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

	BattleCommand* newCommand = new BattleCommand();
	availableCommands.push_back(newCommand);
	newCommand = new Fight();
	availableCommands.push_back(newCommand);
	newCommand = new ItemCMD();
	availableCommands.push_back(newCommand);
	newCommand = new Run();
	availableCommands.push_back(newCommand);
	newCommand = new Elemental();
	availableCommands.push_back(newCommand);

	commands[0] = availableCommands[1];
	commands[1] = availableCommands[4];
	commands[2] = availableCommands[2];
	commands[3] = availableCommands[3];

	weapon = (Staff*)ItemFactory::instance()->getItem("Splintered Staff");
	armor = (Armor*)ItemFactory::instance()->getItem("Clothes");

	acc1 = NULL;
	acc2 = NULL;
	rune1 = NULL;
	rune2 = NULL;

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
	xpToLevel += (int)((float) xpToLevel * 0.3f);
	if(stats.level == 20)
		xpToLevel = 0;
	}
	
}

ItemStats* Laz::getItemStatsForSlot( int slot)
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
Item* Laz::getItem(int slot)
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

void Laz::addXP(int amount)
{
	stats.xp += amount;
	if(stats.xp >= xpToLevel)
		levelUp();
};
void Laz::adjustResource(int amount)
{
	mana += amount;
	if(mana <=0 )
		mana = 0;
	if (mana >= manaMax)
		mana = manaMax;
};

void Laz::getSkills(std::vector<BattleCommand*>& skillList, int type)
{
	for(int i = 0; i < skills.size(); i++){
		Skill * skill = (Skill*)skills[i];
		if(skill->getType() == type){
			skillList.push_back(skill);
		}
	}
};