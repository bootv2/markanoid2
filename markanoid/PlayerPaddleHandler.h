#pragma once
class PlayerPaddleHandler
{
private:
	Paddle* pPlyPaddle;
	int *windowWidth, *windowHeight;
	float* globalPaddleVelocity;
public:
	PlayerPaddleHandler::PlayerPaddleHandler(int *wW, int *wH, float* globPvelocity)
	{
		globalPaddleVelocity = globPvelocity;
		windowHeight = wH;
		windowWidth = wW;
		pPlyPaddle = new Paddle(*wW, *wH);
		pPlyPaddle->setPaddleVelocity(*globPvelocity);
	}


	PlayerPaddleHandler::~PlayerPaddleHandler()
	{
		delete pPlyPaddle;
	}

	Paddle* PlayerPaddleHandler::getPPaddle()
	{
		return pPlyPaddle;
	}

	void PlayerPaddleHandler::updatePaddle()
	{
		pPlyPaddle->update();
	}

	void PlayerPaddleHandler::pausedUpdate()
	{
		pPlyPaddle->pauseUpdate();
	}

	void PlayerPaddleHandler::resetPaddle()
	{
		delete pPlyPaddle;
		pPlyPaddle = new Paddle(*windowWidth, *windowHeight);
		pPlyPaddle->setPaddleVelocity(*globalPaddleVelocity);
	}

	void setGlobPVel(float vel)
	{
		pPlyPaddle->setPaddleVelocity(vel);
	}

	void PlayerPaddleHandler::drawPaddle(sf::RenderWindow* rWin)
	{
		rWin->draw(pPlyPaddle->shape);
	}
};

