#pragma once
class KeyBinds
{
	std::map<int, sf::Keyboard::Key> bindMap;
	std::map<int, char> keyCharMap;
public:
	bool movePaddleRight, movePaddleLeft, rotateBallLeft, rotateBallRight, nextPowerup, lastPowerup, firePowerup, pause;
	KeyBinds();
	void updatePressedKeys();
	void resetPressedKeys();
	void bindKey(int id, sf::Keyboard::Key bindTo);
	char getCharFromKey(int id);
	void setCharToKeymap(int id, char key);
	~KeyBinds();
};

