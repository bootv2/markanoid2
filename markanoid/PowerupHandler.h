#pragma once

#define ptrArgs SoundMan* _sman, sf::RenderWindow* _pRenderWindow, Paddle* _pPaddle, std::vector<Block>* _blckStor, std::vector<Ball>* _bStor, int* _score, int* _ballAmount, int* _availableLives, ResMan* _res, float* _powContainerFallSpeed, BallContainer* _pBallCont

class PowerupHandler
{
private:
	//private variables
	std::vector<int> powIdStorage;//the position identifier of the vector is the powID, the value inside is the amount of that id currently available
	std::vector<std::string> powPaths;
	BallContainer* pBallContainer;
	SoundMan* sndManager;
	int selectedPowID, maxPowID, windowHeight, windowWidth;
	sf::CircleShape powShape;
	sf::CircleShape* drawableContainerShape;
	ResMan* pResourceMan;
	Paddle* playerPaddle;
	std::vector<Block>* pBlockStorage;
	std::vector<Ball>* pBallStorage;
	std::vector<std::vector<Timer>> timerStorage;
	int* ballAmount, *score, *availableLives;
	Ball* defBall;
	std::vector<PowerupContainer> powContainer;
	float* powContainerFallSpeed;
	sf::RenderWindow* pRenderWindow;
	Timer powTimer;
	Timer focusTimer;
	//private functions

	void drawAvailableLives()
	{
		powShape.setRadius(10.f);
		powShape.setTexture(pResourceMan->getTexture("heart.png"));
		for (int i = 0; i < *availableLives; i++)
		{
			powShape.setPosition(sf::Vector2f(windowWidth - (25.f * i), 25.f));
			pRenderWindow->draw(powShape);
		}
	}

	//the laser collision
	void PowerupHandler::laserCollision()
	{
		sf::RectangleShape tLaserShape;
		tLaserShape.setSize(sf::Vector2f(playerPaddle->shape.getSize().x, windowHeight));
		tLaserShape.setPosition(sf::Vector2f(playerPaddle->left(), 0));
		for (int i = 0; i < pBlockStorage->size(); i++)
		{
			if (pBlockStorage->at(i).destroyed) continue;
			else
			{
				if (!isIntersecting(tLaserShape, pBlockStorage->at(i))) continue;
				else
				{
					*score++;
					pBlockStorage->at(i).destroyed = true;
				}
			}
		}
	}

	//Print the available powerups, originCoords = the top left corner of the printing space, the size of this space can get quite
	//big so make sure theres enough free room around originCoords
	void PowerupHandler::drawAvailablePowerups()
	{
		for (int i = 0; i < maxPowID; i++)
		{
			powShape.setTexture(pResourceMan->getTexture(powPaths.at(i)));
			if (i == selectedPowID) powShape.setRadius(13.5f);
			else powShape.setRadius(10.f);//The powerup focused on is bigger than those that arent focused on
			for (int x = 0; x < powIdStorage.at(i); x++)
			{
				powShape.setPosition(10.f + (30 * i), 15.f + (30 * x));
				pRenderWindow->draw(powShape);
			}
		}
		powShape.setRadius(20.f);
	}

	//use the currently selected powerup!
	//powerup effects are taken care of internally
	//the powerup is only used if space is pressed
	void PowerupHandler::updatePowerupUsage()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (powIdStorage.at(selectedPowID) <= 0) return;
			if (powTimer.getElapsedTime() > 250)
			{
				sndManager->playPowSound(selectedPowID);
				powIdStorage.at(selectedPowID)--;
				powTimer.reset();
				Timer tmp;
				switch (selectedPowID)
				{
				case 0:
					laserCollision();
					break;

				case 1:
					pBallContainer->activateTripleBall();
					std::cout << "pBallStorage.size() = " << pBallStorage->size() << std::endl;
					//system("pause");
					break;

				case 2:
					playerPaddle->powerup();
					tmp.setReturnVal(false);
					tmp.setTimer(10000);//10 seconds
					timerStorage.at(selectedPowID).emplace_back(tmp);
					//system("pause");
					break;

				case 3:
					*availableLives++;
					std::cout << *availableLives << std::endl;
					//system("pause");
					break;

				case 4:
					tmp.setReturnVal(false);
					tmp.setTimer(10000);//10 seconds
					timerStorage.at(selectedPowID).emplace_back(tmp);
					for (int i = 0; i < pBallStorage->size(); i++) pBallStorage->at(i).activateSlow();
					//system("pause");
					break;

				case 5:
					tmp.setReturnVal(false);
					tmp.setTimer(5000);
					timerStorage.at(selectedPowID).emplace_back(tmp);
					for (int i = 0; i < pBallStorage->size(); i++) pBallStorage->at(i).activateBigBall();
					break;

				default:
					if (debug)
					{
						std::cout << "powID error occurred, the powID we got wasnt listed to any powerups! powID is: " << std::to_string(selectedPowID) << std::endl;
						system("PAUSE");
					}
					break;
				}
			}
		}
	}

	void PowerupHandler::updateFocusedPowerupClass()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (focusTimer.getElapsedTime() > 100)
			{
				focusTimer.reset();
				if (selectedPowID + 1 > maxPowID) selectedPowID = 0;
				else selectedPowID++;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (focusTimer.getElapsedTime() > 100)
			{
				focusTimer.reset();
				if (selectedPowID - 1 < 0) selectedPowID = maxPowID;
				else selectedPowID--;
			}
		}
	}

	//debug variables
	bool debug;


public:
	void newGame()
	{
		for (int i = 0; i < maxPowID; i++)
		{
			powIdStorage.at(i) = 2;
			timerStorage.at(i).clear();
		}
		powContainer.clear();
	}

	PowerupHandler::PowerupHandler()
	{
		powShape.setRadius(20);
		powShape.setRadius(10);
		powPaths.emplace_back("laser.png");
		powPaths.emplace_back("tripleball.png");
		powPaths.emplace_back("widepaddle.png");
		powPaths.emplace_back("heart.png");
		powPaths.emplace_back("slow.png");

		for (int i = 0; i < powPaths.size(); i++)
		{
			timerStorage.emplace_back(std::vector<Timer>());
			powIdStorage.emplace_back(0);//initialise a spot in the vector for powerups categorised by powID. powIdStorage.at(powID) returns the amount of uses left of the powID
		}

		maxPowID = powPaths.size();

		powTimer.setReturnVal(false);
		focusTimer.setReturnVal(false);
	}


	PowerupHandler::~PowerupHandler()
	{
		delete defBall;
	}

	//checks if the powerup timers have run out, and if they have, disables the powerups the timers ran out for
	void PowerupHandler::checkTimers()
	{
		for (int i = 0; i < timerStorage.size(); i++)
		{
			for (int y = 0; y < timerStorage.at(i).size(); y++)
			{
				if (timerStorage.at(i).at(y).active)
				{
					if (!timerStorage.at(i).at(y).timeLeft())
					{
						timerStorage.at(i).at(y).active = false;
						switch (i)
						{
						case 2:
							playerPaddle->powReset();
							break;

						case 4:
							for (int x = 0; x < pBallStorage->size(); x++)
							{
								pBallStorage->at(x).deactivateSlow();
							}
							break;

						case 5:
							for (auto& Ball : *pBallStorage) Ball.deactivateBigBall();
							break;

						default:
							if (debug)
							{
								std::cout << "PowerupHandler::checkTimers() tried to disable a powerup without a timer, powID: " << std::to_string(i) << std::endl;
								system("PAUSE");
							}
							break;
						}
					}
				}
			}
		}
	}

	void PowerupHandler::setDebug(bool dbg)
	{
		debug = dbg;
	}



	//bind the pointers needed for powerup interaction with the engine.
	//This function is a REQUIRED function to be able to use the powerup handler.
	void PowerupHandler::bindPointers(ptrArgs)
	{
		pBallContainer = _pBallCont;
		sndManager = _sman;
		playerPaddle = _pPaddle;
		pBlockStorage = _blckStor;
		pBallStorage = _bStor;
		score = _score;
		ballAmount = _ballAmount;
		availableLives = _availableLives;
		pResourceMan = _res;
		powContainerFallSpeed = _powContainerFallSpeed;
		pRenderWindow = _pRenderWindow;
		defBall = new Ball(0, 0, windowHeight, windowWidth, pResourceMan->getTexture("Ball"));
	}

	//sets the maximum PowID to use with powerup shifting and the powerup vector
	void PowerupHandler::setMaxPowID(int _maxPowID)
	{
		maxPowID = _maxPowID;
		for (int i = 0; i < maxPowID; i++) timerStorage.emplace_back(std::vector<Timer>());//for every powerup type, create a vector of timers,
	}

	//Add a powerup to the Powerup handler ID storage(powIdStorage.emplace_back(powID))
	void PowerupHandler::addPowerup(int powID)
	{
		powIdStorage.emplace_back(powID);
	}




	//changes the focused powerup class, the focused powerup class is the class of powerup used when space is pressed


	void PowerupHandler::addPowContainer(Block& mBlock)
	{
		powContainer.emplace_back(PowerupContainer(mBlock, *powContainerFallSpeed, maxPowID, pResourceMan, powPaths));
	}

	void PowerupHandler::updateAll()
	{
		for (auto& PowerupContainer : powContainer)
		{
			PowerupContainer.setFallingSpeed(*powContainerFallSpeed);
			if (PowerupContainer.existing())
			{
				PowerupContainer.update();
				drawableContainerShape = PowerupContainer.getShapeAddress();
				if (isIntersecting(PowerupContainer, *playerPaddle))
				{
					powIdStorage.at(PowerupContainer.getPowID())++;
					PowerupContainer.setExisting(false);
				}
			}
		}
		updatePowerupUsage();
		updateFocusedPowerupClass();
		checkTimers();
	}

	void PowerupHandler::pausedUpdateAll()
	{
		for (auto& PowerupContainer : powContainer) PowerupContainer.pausedUpdate();
	}

	void PowerupHandler::drawAll()
	{
		drawAvailableLives();
		drawAvailablePowerups();
		for (auto& PowerupContainer : powContainer)
		{
			if (PowerupContainer.existing())
			{
				drawableContainerShape = PowerupContainer.getShapeAddress();
				pRenderWindow->draw(*drawableContainerShape);
			}
		}
	}

};
