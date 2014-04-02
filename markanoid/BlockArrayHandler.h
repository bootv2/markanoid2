#pragma once
class BlockArrayHandler
{
private:
	std::vector<Block> blockStorage;
	std::vector<Ball>* pBallStorage;
	PowerupHandler* pGlobPowHandler;
	SoundMan* sndManager;
	LastFrameCollisions blockCollisions;
	int *windowWidth, *windowHeight, *score, *framenum;
	float powContainerFallingSpeed;
public:
	BlockArrayHandler::BlockArrayHandler(int* wW, int* wH, int* _pscore, int* fNum, PowerupHandler* _pgpowHandle, float _powFall, SoundMan* _sndman)
	{
		sndManager = _sndman;
		powContainerFallingSpeed = _powFall;
		pGlobPowHandler = _pgpowHandle;
		framenum = fNum;
		score = _pscore;
		windowHeight = wH;
		windowWidth = wW;
		int seed = 0;
		for (int i = 50; i < *windowWidth - 50; i += 65)
		{
			for (int x = 80; x < *windowHeight / 2; x += 25)
			{
				blockStorage.emplace_back(Block(sf::Vector2f(i, x), rand()%5, sndManager));
			}
		}
	}

	void newGame()
	{
		blockStorage.clear();
		for (int i = 50; i < *windowWidth - 50; i += 65)
		{
			for (int x = 80; x < *windowHeight / 2; x += 25)
			{
				blockStorage.emplace_back(Block(sf::Vector2f(i, x), rand()%5, sndManager));
			}
		}
	}


	BlockArrayHandler::~BlockArrayHandler()
	{
	}

	void BlockArrayHandler::setPBallStorage(std::vector<Ball>* _pvBall)
	{
		pBallStorage = _pvBall;
	}

	void BlockArrayHandler::drawAll(sf::RenderWindow* pWin)
	{
		for (auto& Block : blockStorage)
		{
			Block.draw(pWin);
		}
	}

	void BlockArrayHandler::testCollisions()
	{
		
		for (auto& Block : blockStorage)
		{
			if (Block.hit)
			{
				Block.hit = false;
				if (rand()%100 < 10)
					pGlobPowHandler->addPowContainer(Block);
			}
		}
	}

	std::vector<Block>* BlockArrayHandler::getPBlockStorage()
	{
		return &blockStorage;
	}
};

