#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

Player* Player::instance()
{
	static Player player;
	return &player;
}

void Player::init()
{
	inventory.clear();
	team.clear();

	grem = Grem::instance();
	grem->init();
	team.push_back(grem);

	lenn = Lenn::instance();
	lenn->init();
	team.push_back(lenn);

	laz = Laz::instance();
	laz->init();
	team.push_back(laz);

	gold = 10000;

	Item* potion = ItemFactory::instance()->getItem("Potion");
	potion->setAmount(1);
	inventory.push_back(potion);
	
	Item* ether = ItemFactory::instance()->getItem("Ether");
	ether->setAmount(1);
	inventory.push_back(ether);

	Item* revive = ItemFactory::instance()->getItem("Revive");
	revive->setAmount(1);
	inventory.push_back(revive);

	completedFifth = false;
	completedTenth = true;
}
void Player::shutdown()
{
}

void Player::addItem(Item* item)
{
	if(inventory.empty())
		inventory.push_back(item);
	else {
		for(int i = 0; i < inventory.size(); i++) {
			if(item->getStats().name == inventory[i]->getStats().name){
				if(inventory[i]->getAmount() +item->getAmount() < 100){
					inventory[i]->setAmount(inventory[i]->getAmount() +item->getAmount());
					return;
				}
			}
		}
	}
	if(inventory.size() < INVENTORY_CAP)
		inventory.push_back(item);
}

void Player::removeItem(Item item)
{
	if(inventory.empty())
		return;
	else {
		for(int i = 0; i < inventory.size(); i++) {
			if(item.getStats().name == inventory[i]->getStats().name){
				// check amount to remove if amount brings  total amount of item to 0 or lower remove and delete item
				int amtToRemove = item.getAmount();
				int amtInInventory = inventory[i]->getAmount();
				if(amtToRemove >= amtInInventory) {
					//delete inventory[i];
					inventory.erase(inventory.begin()+i);
				}
				else 
					inventory[i]->setAmount(amtInInventory - amtToRemove);
				return;
			}
		}
	}
}

std::vector<Item*>* Player::getInventory()
{
	return &inventory;
}

void Player::adjustGold(int amount)
{
	gold += amount;
	if(gold > 99999)
		gold = 99999;
	if(gold <= 0)
		gold = 0;
}
int Player::getGold()
{
	return gold;
}

void Player::fifthComplete()
{
	completedFifth = true;
}

bool Player::hasCompletedFifth()
{
	return completedFifth;
}


void Player::tenthComplete()
{
	completedTenth = true;
}

bool Player::hasCompletedtenth()
{
	return completedTenth;
}
