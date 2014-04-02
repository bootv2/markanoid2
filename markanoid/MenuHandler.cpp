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
#include "SettingsMenu.h"
#include "MainMenu.h"


#include "MenuHandler.h"


MenuHandler::MenuHandler(sf::RenderWindow* _pRenderWindow, BallContainer* bCont, PlayerPaddleHandler* pPaddle, PowerupHandler* ppowhand)
{
	pRenderWindow = _pRenderWindow;
	pBallContainer = bCont;
	playerPaddle = pPaddle;
	powHandler = ppowhand;
	sfg::SFGUI *tgui = new sfg::SFGUI();
	guiStor.emplace_back(*tgui);
	//delete tgui;
	tgui = new sfg::SFGUI();
	guiStor.emplace_back(*tgui);
	mainMenuPTR = new MainMenu(pRenderWindow, pBallContainer, playerPaddle, powHandler, &guiStor.at(0));
	setmenu = new SettingsMenu();
	setmenu->bindPTR(NULL, NULL, NULL, pRenderWindow, &guiStor.at(1));
}

void MenuHandler::setMenu(int index)
{
	menuIndex = index;
}

void MenuHandler::setSettingPTR(float* ptr1, float* ptr2, float* ptr3)
{
	setmenu->bindPTR(ptr1, ptr2, ptr3, pRenderWindow, &guiStor.at(1));
}

bool MenuHandler::runMenu()
{
	inMenu = true;
	while (inMenu)
	{
		switch (menuIndex)
		{
		case -1:
			menuIndex = mainMenuPTR->enter();
			break;

		case 0:
			//return and play game;
			//--exit menu system game object update!
			powHandler->pausedUpdateAll();
			playerPaddle->pausedUpdate();
			pBallContainer->pausedUpdateAll();
			//!-/exit meny system game object update
			inMenu = false;
			return false;
			break;

		case 1:
			//return and exit game;
			return true;
			break;

		case 2: 
			//enter settings menu.
			menuIndex = setmenu->run();
			break;
		default:
			throw 1000;
			break;
		}
	}
}

MenuHandler::~MenuHandler()
{
}
