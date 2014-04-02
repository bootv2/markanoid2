#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>

#include "ControlsMenu.h"


ControlsMenu::ControlsMenu()
{
	auto moveright = sfg::Button::Create("Move paddle right");
	auto moveleft = sfg::Button::Create("Move paddle left");
	auto rotateleft = sfg::Button::Create("Rotate ball left");
	auto rotateright = sfg::Button::Create("Rotate ball right");
	auto nextpow = sfg::Button::Create("Select next powerup");
	auto lastpow = sfg::Button::Create("Select last powerup");
	auto firepow = sfg::Button::Create("Use powerup");
	auto pause = sfg::Button::Create("Pause/menu");
	
	/*auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");
	auto but = sfg::Label::Create("apply");*/


}


ControlsMenu::~ControlsMenu()
{
}
