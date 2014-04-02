#pragma once
class Score
{
	int *score;
	sf::Font scoreFont;
	sf::Text scoreText;
	sf::RenderWindow* pRenderWindow;
	int *windowWidth, *windowHeight;
	int multiplier = 0;
	Timer multiplierTimer;
	int multiplierScore = 0;
public:
	Score(sf::RenderWindow* _pRW, int* wW, int* wH);
	~Score();
	int* getScoreAddress();
	void printScore();
	void printMultiplier();
	Score& operator+(int addition)
	{
		if (multiplier == 0)
		{
			multiplierTimer.active = true;
			multiplierTimer.setTimer(3000);//3000 ms multiplier time
			//TODO: schale the multiplier time by difficulty
		}
		multiplier++;
		multiplierScore += addition;

	}
};

