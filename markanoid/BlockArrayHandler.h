#pragma once
class BlockArrayHandler
{
private:
	std::vector<Block> blockStorage;
	std::vector<Ball>* pBallStorage;
	PowerupHandler* pGlobPowHandler;
	SoundMan* sndManager;
	Score* pScore;
	ResMan* prMan;
	LastFrameCollisions blockCollisions;
	int *windowWidth, *windowHeight, *score, *framenum;
	float powContainerFallingSpeed;
public:
	BlockArrayHandler::BlockArrayHandler(int* wW, int* wH, Score* _pScore, int* fNum, PowerupHandler* _pgpowHandle, float _powFall, SoundMan* _sndman, ResMan* _prMan)
	{
		sndManager = _sndman;
		powContainerFallingSpeed = _powFall;
		pGlobPowHandler = _pgpowHandle;
		framenum = fNum;
		pScore = _pScore;
		prMan = _prMan;
		windowHeight = wH;
		windowWidth = wW;
		int seed = 0;
		for (int i = 50; i < *windowWidth - 50; i += 65)
		{
			for (int x = 80; x < *windowHeight / 2; x += 25)
			{
				blockStorage.emplace_back(Block(sf::Vector2f(i, x), rand()%5, sndManager, prMan));
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
				blockStorage.emplace_back(Block(sf::Vector2f(i, x), rand()%5, sndManager, prMan));
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
				if (Block.hp == 0)
					pScore->addscore(5, "Block destroyed: 5 points", Block.shape.getPosition());
				else
					pScore->addscore(1, "Block hit: 1 points", Block.shape.getPosition());
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

