#pragma once
class MenuHandler
{
private:
	std::vector<sfg::SFGUI> guiStor;
	int menuIndex;
	bool inMenu = true;
	sf::RenderWindow* pRenderWindow;

	//settings menu variables
	//TODO

	//Menu Variables
	MainMenu* mainMenuPTR;
	SettingsMenu* setmenu;

	//game variables that need to be tracked:
	PowerupHandler* powHandler;
	PlayerPaddleHandler* playerPaddle;
	BallContainer* pBallContainer;
public:
	MenuHandler(sf::RenderWindow* _pRenderWindow, BallContainer* bCont, PlayerPaddleHandler* pPaddle, PowerupHandler* ppowhand);
	void setMenu(int index);
	bool runMenu();
	void setSettingPTR(float* ptr1, float* ptr2, float* ptr3);
	~MenuHandler();
};

