#pragma once
class BallContainer
{
private:
	std::vector<Ball> ballContainer;
	Ball* defaultBall;
	ResMan* globResMan;
	int windowWidth, windowHeight;

	Timer frameTime;

	int* ballAmount, *availableLives;
	float leftoverTime = 0;
	float elapsedTime = 0;

	sf::RenderWindow* pRenderWindow;
public:
	//Initialise the Ballcontainer(windowWidth and windowHeight are used to calculate the position of the default ball
	BallContainer(int _windowWidth, int _windowHeight, ResMan* _res, sf::RenderWindow* _pRenderWindow, int* _availableLives, int* _ballAmount)
	{
		availableLives = _availableLives;
		ballAmount = _ballAmount;
		pRenderWindow = _pRenderWindow;
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;
		globResMan = _res;
		//Create a default ball with default coordinates originating at half the windowWidth and about the height of the paddle
		defaultBall = new Ball(windowWidth / 2, (windowHeight / 2) + ((windowHeight / 2) - 50), windowHeight, windowWidth, globResMan->getTexture("ball.png"));
		ballContainer.emplace_back(*defaultBall);
		frameTime.reset();
	}

	std::vector<Ball>* getBallVectorAddress()
	{
		return &ballContainer;
	}

	~BallContainer()
	{
		delete defaultBall;
	}

	void newGame()
	{
		*ballAmount = 0;
		ballContainer.clear();
		delete defaultBall;
		defaultBall = new Ball(windowWidth / 2, (windowHeight / 2) + ((windowHeight / 2) - 50), windowHeight, windowWidth, globResMan->getTexture("ball.png"));
		ballContainer.emplace_back(*defaultBall);
	}

	void activateTripleBall()
	{
		int amountOfBallsBeforeLoop = ballContainer.size();
		for (int i = 0; i < amountOfBallsBeforeLoop; i++)
		{
			delete defaultBall;
			defaultBall = new Ball(windowWidth / 2, (windowHeight / 2) + ((windowHeight / 2) - 50), windowHeight, windowWidth, globResMan->getTexture("ball.png"));
			defaultBall->shape.setPosition(ballContainer.at(i).shape.getPosition().x - 20, ballContainer.at(i).shape.getPosition().y - 20);
			defaultBall->setVelocity(ballContainer.at(0).getVelocity());
			ballContainer.emplace_back(*defaultBall);
			delete defaultBall;
			defaultBall = new Ball(windowWidth / 2, (windowHeight / 2) + ((windowHeight / 2) - 50), windowHeight, windowWidth, globResMan->getTexture("ball.png"));
			defaultBall->setVelocity(ballContainer.at(0).getVelocity());
			defaultBall->shape.setPosition(ballContainer.at(i).shape.getPosition().x + 20, ballContainer.at(i).shape.getPosition().y + 20);
			std::cout << defaultBall->shape.getPosition().x << " : " << defaultBall->shape.getPosition().y;
			ballContainer.emplace_back(*defaultBall);
		}
		*ballAmount = *ballAmount * 3;

		//std::cout << "The amount of balls is now " << ballContainer.size() << " according to ballcontainer.\n";
		//std::cout << "It is " << *ballAmount << " according to *ballamount!";
	}

	void updateAll(Paddle* _pPaddle, std::vector<Block>* pBlockArray)
	{
		elapsedTime += frameTime.reset();
		//std::cout << std::to_string(elapsedTime) << std::endl;
		//std::cout << "ballContainerSize = " << ballContainer.size() << std::endl;
		for (int i = 0; i < ballContainer.size(); i++)
		{
			for (; elapsedTime > 1; elapsedTime -= 1)
			{
				if(ballContainer.size() > 0) ballContainer.at(i).update(1.f);
				for (int y = 0; y < pBlockArray->size(); y++)
				{
					if (pBlockArray->at(y).hp == 0) continue;
                    pBlockArray->at(y).testCollision(&ballContainer.at(i));
				}
				if (isIntersecting(ballContainer.at(i), *_pPaddle))
				{
					ballContainer.at(i).velocity.y = -ballContainer.at(i).ballVelocity;
					if (ballContainer.at(i).x() < _pPaddle->x())	ballContainer.at(i).velocity.x = -ballContainer.at(i).ballVelocity;
					else											ballContainer.at(i).velocity.x = ballContainer.at(i).ballVelocity;
				}
				if (ballContainer.at(i).top() > windowHeight)
				{
					if (*availableLives > 0)
					{
						*availableLives--;
						ballContainer.at(i).velocity.y = -ballContainer.at(i).ballVelocity;
					}
					else
					{
						*ballAmount--;
						ballContainer.erase(ballContainer.begin() + i);
						ballContainer.shrink_to_fit();
					}
				}
			}
		}
	}

	void pausedUpdateAll()
	{
		frameTime.reset();
		for (auto& Ball : ballContainer)
		{
			Ball.pauseUpdate();
		}
	}

	void drawAll()
	{
		for (auto& Ball : ballContainer) pRenderWindow->draw(Ball.shape);
	}
};

