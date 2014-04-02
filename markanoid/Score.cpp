#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "timer.h"

#include "Score.h"


Score::Score(sf::RenderWindow* _pRW, int* wW, int* wH)
{
	score = new int(0);
	pRenderWindow = _pRW;
	windowWidth = wW;
	windowHeight = wH;
	scoreFont.loadFromFile("arial.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setPosition(sf::Vector2f(*windowWidth - 200, 20));
	multiplierTimer.reset();
	multiplierTimer.active = false;
}


Score::~Score()
{
}

void Score::printScore()
{
	std::cout << "score: " << *score << std::endl;
	scoreText.setString(std::to_string(*score));
	pRenderWindow->draw(scoreText);
}

int* Score::getScoreAddress()
{
	return score;
}