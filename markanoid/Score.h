#pragma once
class Score
{
	int *score;
	sf::Font scoreFont;
	sf::Text scoreText;
	sf::Text multiplierText;
	sf::Text multiplierTimerText;
	sf::RectangleShape timerbar[2];
	sf::Text multiplierScoreText;
	std::vector<sf::Text> scoreTexts;
	std::vector<Timer> scoreTextTimers;
	sf::RenderWindow* pRenderWindow;
	int *windowWidth, *windowHeight;
	int multiplier = 1;
	int multiplierTime = 1000;
	Timer multiplierTimer;
	int multiplierScore = 0;
	ResMan* prMan;
public:
	Score(sf::RenderWindow* _pRW, int* wW, int* wH, ResMan* pResMan);
	~Score();
	int* getScoreAddress();
	void printScore();
	void printMultiplier();
	void addscore(int addition, std::string scoretext, sf::Vector2f scoreCoords);
	void updateAll();
};

