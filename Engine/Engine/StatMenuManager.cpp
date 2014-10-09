#include "StatMenuManager.h"
#include "statusStates.h"
#include "Options.h"


StatMenuManager::StatMenuManager()
{}

StatMenuManager::~StatMenuManager()
{}

StatMenuManager *StatMenuManager::instance()
{
	static StatMenuManager menu;
	return &menu;

}

void StatMenuManager::init()
{
	while(!statusState.empty())
		statusState.pop();
	statusState.push(StatusMain::instance());
	statusState.top()->init();

	InventoryScreen::instance()->init();
	EquipScreen::instance()->init();
	SkillsMenu::instance()->init();
	StatusScreen::instance()->init();
}

void StatMenuManager::shutdown()
{

}

int StatMenuManager::update()
{
	Engine::Input* input = Engine::Input::instance();

	if(input->push_button(DIK_G)){
		if(!input->check_button_down(DIK_G)){
			input->set_button(DIK_G,true);
			// empty stack except mainmenu
			while(!statusState.empty())
				statusState.pop();
			statusState.push(StatusMain::instance());
			return GameStates::RETURN;
		}
	} else input->set_button(DIK_G,false);

	if(statusState.empty())
		statusState.push(StatusMain::instance());
	int switch_on = statusState.top()->update();

	switch (switch_on)
	{
	case STATUS_STATE::MAIN:
		while(!statusState.empty())
			statusState.pop();
		statusState.push(StatusMain::instance());
		break;
	case STATUS_STATE::INVENTORY:
		// InventoryScreen::instance()->setBool(true);
		statusState.push(InventoryScreen::instance());
		break;
	case STATUS_STATE::EQUIP:
		statusState.push(EquipScreen::instance());
		break;
	case STATUS_STATE::SKILLS:
		statusState.push(SkillsMenu::instance());
		break;
	case STATUS_STATE::STATUS:
		statusState.push(StatusScreen::instance());
		break;
	case STATUS_STATE::OPTIONS:
		statusState.push(Options::instance());
		break;
	case GameStates::RETURN:
		statusState.pop();
		break;
	default:
		break;
	}
	return 0;
}

void StatMenuManager::render()
{
	if(!statusState.empty())
		statusState.top()->render();
}
