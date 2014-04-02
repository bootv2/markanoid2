#include <SFGUI\SFGUI.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "ResMan.cpp"
#include "Settings.cpp"
#include "FileIO.cpp"
#include "PowerupHandler.cpp"
#include "PlayerPaddleHandler.cpp"
#include "BlockArrayHandler.cpp"
#include "BallContainer.cpp"
#include "Score.h"
#include "MainMenu.h"



MainMenu::MainMenu(sf::RenderWindow* prWindow, BallContainer* bCont, PlayerPaddleHandler* pPaddle, PowerupHandler* ppowhand, sfg::SFGUI* _gui)
{
	gui = _gui;
	powHandler = ppowhand;
	playerPaddle = pPaddle;
	pBallContainer = bCont;
	pRWindow = prWindow;
	//create a button and store it inside the button(widget) storage
	auto button = sfg::Button::Create("play");
	auto options = sfg::Button::Create("Options");
	auto exit = sfg::Button::Create("exit");
	buttonStorage.emplace_back(button);
	buttonStorage.emplace_back(options);
	buttonStorage.emplace_back(exit);
	
	//bind the play button to the play function using std::bind();
	buttonStorage.at(0)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenu::playButtonClicked, this));
	buttonStorage.at(1)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenu::optionsClicked, this));
	buttonStorage.at(2)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenu::exitButtonClicked, this));
	//label creation for the box
	m_label = sfg::Label::Create("Main Menu");
	//box creation
	box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	//packing elements into the box
	box->Pack(m_label);
	for (int i = 0; i < buttonStorage.size(); i++)
	{
		box->Pack(buttonStorage.at(i), false);
	}
	//creating a sfg window
	window = sfg::Window::Create();
	//add elements and boxes to window
	window->SetTitle("Markanoid Main Menu");
	window->Add(box);
	window->SetAllocation(sf::FloatRect(0, 0, 1900, 1000));
	//desktop creation and window insertion
	desktop.Add(window);
}

void MainMenu::changeResClicked()
{
	pRWindow->create(sf::VideoMode(800, 600), "res now 800*600");
}

int MainMenu::enter()
{
	window->Show(true);
	int ret;
	//need to reset ogl states
	pRWindow->resetGLStates();

	//set events and clock for the main loop!
	sf::Event event1;
	sf::Clock clock;

	//while the play button isnt clicked stay in main menu
	while (!buttonClicked)
	{
		//event handling
		while (pRWindow->pollEvent(event1))
		{
			desktop.HandleEvent(event1);
			//if the window is closed leave the program
			if (event1.type == sf::Event::Closed)
				pRWindow->close();
		}
		//update sfgui using the clock delta time
		powHandler->pausedUpdateAll();
		playerPaddle->pausedUpdate();
		pBallContainer->pausedUpdateAll();


		desktop.Update(clock.restart().asSeconds());
		pRWindow->clear();
		gui->Display(*pRWindow);
		pRWindow->display();
	}
	buttonClicked = false;
	if (exitButtonIsClicked) ret =  1;//exit
	if (playButtonIsClicked) ret = 0;//play
	if (optionsButtonClicked) ret = 2;//options
	window->Show(false);
	optionsButtonClicked = false;
	exitButtonIsClicked = false;
	playButtonIsClicked = false;
	return ret;

}

void MainMenu::playButtonClicked()
{
	buttonClicked = true;
	playButtonIsClicked = true;
}

void MainMenu::exitButtonClicked()
{
	buttonClicked = true;
	exitButtonIsClicked = true;
}

void MainMenu::optionsClicked()
{
	optionsButtonClicked = true;
	buttonClicked = true;
}


MainMenu::~MainMenu()
{
}
