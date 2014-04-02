#pragma once
class Engine
{
private:
	//Make pointers for the sf videomode and renderwindow so other objects can also access these variables
	sf::VideoMode* vidMode;
	sf::RenderWindow* rWindow;

	PlayerPaddleHandler* playerPaddle;//TODO: replace the pointers to objects in function statements with (Class& object) instead of(Class* object)

	//pointer to the resourseManager
	ResMan* resourceMan;

	SoundMan* sndMan;

	//setting Object
	Settings set;

	//Menu system handler
	MenuHandler* menuHandle;

	//Initialize window properties
	int windowWidth, windowHeight, maxFPS;
	int framenum = 0;
	
	sf::Event event;

	//menu management variables
	bool enterMainMenu = true;

	//game variables
	int availableLives = 1;
	int ballAmount = 1;
	int score = 0;
	Score* gameScore;
	PowerupHandler* powHandler;
	float* paddleVelocity, *powContainerFallingSpeed, *ballVelocity;
	BlockArrayHandler* blocksHandler;
	BallContainer* pBallContainer;

	//debug variables
	bool debug;


public:
	Engine::Engine(bool _debug)
	{
		srand(time(NULL));
		sndMan = new SoundMan();
		resourceMan = new ResMan();
		powHandler = new PowerupHandler();
		debug = _debug;
		set.init();
		windowWidth = set.getWindowWidth();
		windowHeight = set.getWindowHeight();
		maxFPS = set.getMaxFPS();

		paddleVelocity = new float(set.getPaddleVelocity());
		powContainerFallingSpeed = new float(set.getPowContFallSpeed());
		ballVelocity = new float(set.getBallVelocity());

		playerPaddle = new PlayerPaddleHandler(&windowWidth, &windowHeight, paddleVelocity);

		vidMode = new sf::VideoMode(windowWidth, windowHeight);

		rWindow = new sf::RenderWindow(*vidMode, "Markanoid");
		rWindow->setFramerateLimit(maxFPS);

		gameScore = new Score(rWindow, &windowWidth, &windowHeight);

		//blocksHandler = new BlockArrayHandler(&windowWidth, &windowHeight, &score, &framenum, powHandler, *powContainerFallingSpeed, sndMan);

		if (!resourceMan->addTexture("laser.png"));// throw 1;//TODO throw exception
		if (!resourceMan->addTexture("tripleball.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("widepaddle.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("heart.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("slow.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("ball.png")) throw 1;

		if (debug) std::cout << "Resource loading succesful!\n";
		gameScore = new Score(rWindow, &windowWidth, &windowHeight);

		blocksHandler = new BlockArrayHandler(&windowWidth, &windowHeight, &score, &framenum, powHandler, *powContainerFallingSpeed, sndMan);

		if (!resourceMan->addTexture("laser.png"));// throw 1;//TODO throw exception
		if (!resourceMan->addTexture("tripleball.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("widepaddle.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("heart.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("slow.png")) throw 1;//TODO throw exception
		if (!resourceMan->addTexture("ball.png")) throw 1;

		if (debug) std::cout << "Resource loading succesful!\n";

		pBallContainer = new BallContainer(windowWidth, windowHeight, resourceMan, rWindow, &availableLives, &ballAmount);

		powHandler->bindPointers(sndMan, rWindow, playerPaddle->getPPaddle(), blocksHandler->getPBlockStorage(), pBallContainer->getBallVectorAddress(),
			&score, &ballAmount, &availableLives, resourceMan, powContainerFallingSpeed, pBallContainer);
		powHandler->setDebug(debug);

		if (debug) std::cout << "powHandler pointer bind successful!\n";

		for (auto& Ball : *pBallContainer->getBallVectorAddress())
			Ball.setVelocity(*ballVelocity);
		blocksHandler->setPBallStorage(pBallContainer->getBallVectorAddress());

		if (debug) std::cout << "pBallContainer created\n";
	}


	Engine::~Engine()
	{
		rWindow->~RenderWindow();
		delete rWindow;
		delete vidMode;
	}

	//run the game
	int Engine::run()
	{
		menuHandle = new MenuHandler(rWindow, pBallContainer, playerPaddle, powHandler);
		menuHandle->setSettingPTR(paddleVelocity, ballVelocity, powContainerFallingSpeed);
		
		if (debug) std::cout << "starting main game loop...\n";
		while (rWindow->isOpen())
		{
			//if (debug) std::cout << "score = " << score << std::endl;
			if (enterMainMenu)
			{
				enterMainMenu = false;
				menuHandle->setMenu(-1);//set the menu handler to start the main menu;
				if (menuHandle->runMenu() == true) return 0;//exit button has been pressed
				for (auto& Ball : *pBallContainer->getBallVectorAddress())//applying new settings to ball, paddle, and powerups
					Ball.setVelocity(*ballVelocity);
				playerPaddle->setGlobPVel(*paddleVelocity);
				//Powhandler falling velocity automatically gets updated...

				//save the new settings...
				set.setVelocities(*ballVelocity, *paddleVelocity, *powContainerFallingSpeed);
				set.saveSettings();
			}

			//if (debug) std::cout << "Start of game loop number " << framenum << std::endl;
			while (rWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					rWindow->close();
					return 0;
				}
			}

			//if (debug) std::cout << "pollEvent done\n";

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				enterMainMenu = true;
			}

			//if (debug) std::cout << "event checks for frame number " << framenum << " done\n";
			//newGame engine function
			if (ballAmount == 0 || pBallContainer->getBallVectorAddress()->size() == 0)
			{
				pBallContainer->newGame();
				powHandler->newGame();
				blocksHandler->newGame();
				score = 0;
				ballAmount = 1;
				availableLives++;
			}

			score = framenum;

			rWindow->clear(sf::Color::Black);
			powHandler->updateAll();
			playerPaddle->updatePaddle();
			pBallContainer->updateAll(playerPaddle->getPPaddle(), blocksHandler->getPBlockStorage());

			//gameScore->printScore();
			blocksHandler->drawAll(rWindow);
			playerPaddle->drawPaddle(rWindow);
			pBallContainer->drawAll();
			powHandler->drawAll();

			rWindow->display();

			//if (debug) std::cout << "drawing for frame number " << framenum << " done\n";
			framenum++;


		}

		return 0;
	}
};

