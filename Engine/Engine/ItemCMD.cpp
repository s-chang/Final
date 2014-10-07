#include "ItemCMD.h"
#include "Battle.h"


ItemCMD::ItemCMD(void) : BattleCommand()
{
	name = "Item";
	help = "Use an item from your inventory";
}


ItemCMD::~ItemCMD(void)
{
}


void ItemCMD::init()
{
}

void ItemCMD::update()
{
	help = "Select an item by clicking its name or right click to return";
	Engine::Input* input = Engine::Input::instance();
	Engine::Cursor*c = Engine::Cursor::instance();
	Battle* b = Battle::instance();
	b->renderNames = false;
	if(input->check_mouse_button(1)){
		b->activeCMD = NULL;
		b->renderNames = true;
		b->turnStatus = TURN_STATUS::START;
		help = "Use an item from your inventory";
		return;
	}
}

void ItemCMD::render()
{

}

void ItemCMD::text()
{
	RECT r2;
	r2.left = 470;
	r2.top = 450;
	Engine::Text* t = Engine::Text::instance();
		t->font->DrawText(0, L"NONE", -1, &r2, 
			DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

std::string ItemCMD::helpText()
{
	return help;
}
