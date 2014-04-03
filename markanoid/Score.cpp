#include <SFML/Graphics.hpp>
#include <sfml/Audio.hpp>
#include <string>
#include <iostream>

#include "resman.h"

#include "timer.h"

#include "Score.h"


Score::Score(sf::RenderWindow* _pRW, int* wW, int* wH, ResMan* pResMan)
{
	score = new int(0);
	pRenderWindow = _pRW;
	prMan = pResMan;
	windowWidth = wW;
	windowHeight = wH;
	scoreFont.loadFromFile("arial.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setPosition(sf::Vector2f(*windowWidth - 200, 5));
	multiplierText.setFont(scoreFont);
	multiplierText.setColor(sf::Color::Green);
	multiplierText.setPosition(sf::Vector2f(*windowWidth - 200, 30));

	timerbar[0].setSize(sf::Vector2f(190, 4));
	timerbar[1].setSize(sf::Vector2f(190, 4));
	timerbar[0].setPosition(sf::Vector2f((*windowWidth / 2) - 95, *windowHeight - 30));
	timerbar[1].setPosition(sf::Vector2f((*windowWidth / 2) - 95, *windowHeight - 30));
	timerbar[0].setTexture(prMan->getTexture("res/txt/kenney.nl/emptyprogress.png"));
	timerbar[1].setTexture(prMan->getTexture("res/txt/kenney.nl/fullprogress.png"));

	multiplierScoreText.setFont(scoreFont);
	multiplierScoreText.setColor(sf::Color::Red);
	multiplierScoreText.setPosition(sf::Vector2f((*windowWidth / 2) - 300, *windowHeight - 30));

	multiplierTimer.reset();
	multiplierTimer.active = false;
}

void Score::addscore(int addition, std::string scoretext, sf::Vector2f scoreCoords)
{
	sf::Text temp;
	temp.setFont(scoreFont);
	temp.setString(scoretext);
	temp.setPosition(scoreCoords);
	temp.setCharacterSize(16.f);

	Timer temp2;
	temp2.active = true;
	temp2.setReturnVal(true);

	scoreTexts.emplace_back(temp);
	scoreTextTimers.emplace_back(temp2);

	multiplier++;
	multiplierScore += addition;

	multiplierTimer.reset();

	if (multiplier == 1)
	{
		multiplierTimer.active = true;
		multiplierTimer.reset();
		multiplierTimer.setReturnVal(false);
		//TODO: schale the multiplier time by difficulty
	}
	
}

void Score::updateAll()
{
	//std::cout << multiplierTimer.getElapsedTime() << "\n";
	for (int i = 0; i < scoreTexts.size(); i++)
	{
		if (scoreTextTimers.at(i).getElapsedTime() > 3)
		{
			//scoreTexts.erase(scoreTexts.begin() + i);
			//scoreTextTimers.erase(scoreTextTimers.begin + i);
			//i--;
			scoreTexts.at(i).setString("");
		}
		else
		{
			scoreTexts.at(i).setPosition(scoreTexts.at(i).getPosition().x, scoreTexts.at(i).getPosition().y - 1);
		}
	}
	if (multiplierTimer.getElapsedTime() > multiplierTime)
	{
		multiplierTimer.active = false;
		*score += multiplier * multiplierScore;
		multiplier = 1;
		multiplierScore = 0;

	}
}


Score::~Score()
{
}

void Score::printScore()
{
	int times = 0;
	//std::cout << "score: " << *score << std::endl;
	scoreText.setString(std::to_string(*score));
	multiplierText.setString("Mult: " + std::to_string(multiplier) + "x");
	multiplierScoreText.setString(std::to_string(multiplierScore));
	if (multiplierTimer.getElapsedTime() < multiplierTime)
	{
		pRenderWindow->draw(multiplierScoreText);

		for (int i = 0; i < multiplierTimer.getElapsedTime(); i++)
		{
			if (i % 25 == 0)
			{
				times++;
			}
		}
		pRenderWindow->draw(timerbar[0]);
		timerbar[1].setSize(sf::Vector2f(times * 4.75f, 4));
		pRenderWindow->draw(timerbar[1]);
	}
	
	
	pRenderWindow->draw(scoreText);
	pRenderWindow->draw(multiplierText);
	for (int i = 0; i < scoreTexts.size(); i++)
	{
		pRenderWindow->draw(scoreTexts.at(i));
	}
}

int* Score::getScoreAddress()
{
	return score;
}