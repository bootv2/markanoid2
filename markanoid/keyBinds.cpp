#include <SFML\Graphics.hpp>
#include <map>
#include "keyBinds.h"


KeyBinds::KeyBinds()//temp unchangeable default keybinds
{
	bindMap[0] = sf::Keyboard::Key::Right;
	keyCharMap[0] = '>';
	bindMap[1] = sf::Keyboard::Key::Left;
	keyCharMap[1] = '<';
	bindMap[2] = sf::Keyboard::Key::A;
	keyCharMap[2] = 'A';
	bindMap[3] = sf::Keyboard::Key::D;
	keyCharMap[3] = 'D';
	bindMap[4] = sf::Keyboard::Key::W;
	keyCharMap[4] = 'W';
	bindMap[5] = sf::Keyboard::Key::S;
	keyCharMap[5] = 'S';
	bindMap[6] = sf::Keyboard::Key::Space;
	keyCharMap[6] = ' ';
	bindMap[7] = sf::Keyboard::Key::Escape;
	keyCharMap[7] = '!';
}

void KeyBinds::bindKey(int id, sf::Keyboard::Key bindTo)
{
	bindMap[id] = bindTo;
}

void KeyBinds::updatePressedKeys()
{
	for (int i = 0; i < 8; i++)
	{
		if (sf::Keyboard::isKeyPressed(bindMap[i]))
		{
			switch (i)
			{
			case 0:
				movePaddleRight = true;
				break;

			case 1:
				movePaddleLeft = true;
				break;

			case 2:
				rotateBallLeft = true;
				break;

			case 3:
				rotateBallRight = true;
				break;

			case 4:
				nextPowerup = true;
				break;

			case 5:
				lastPowerup = true;
				break;

			case 6:
				firePowerup = true;
				break;

			case 7:
				pause = true;
				break;

			}
		}
	}
	
}

void KeyBinds::resetPressedKeys()
{
	movePaddleRight = false;//0
	movePaddleLeft = false;//1
	rotateBallLeft = false;//2
	rotateBallRight = false;//3
	nextPowerup = false;//4
	lastPowerup = false; //5
	firePowerup = false;//6
	pause = false;//7
}

KeyBinds::~KeyBinds()
{
}
