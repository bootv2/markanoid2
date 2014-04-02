#pragma once
class MainMenu
{
private:
	sfg::SFGUI* gui;
	std::vector<sfg::Widget::Ptr> buttonStorage;
	sf::RenderWindow* pRWindow;
	sfg::Label::Ptr m_label;
	bool playButtonIsClicked;
	bool exitButtonIsClicked;
	bool buttonClicked;
	bool optionsButtonClicked;

	PowerupHandler* powHandler;
	PlayerPaddleHandler* playerPaddle;
	BallContainer* pBallContainer;

	//-gui objects
	sfg::Desktop desktop;
	sfg::Window::Ptr window;
	sfg::Box::Ptr box;

	void exitButtonClicked();
	void playButtonClicked();
	void changeResClicked();
	void optionsClicked();
public:
	int enter();
	MainMenu(sf::RenderWindow* prWindow, BallContainer* bCont, PlayerPaddleHandler* pPaddle, PowerupHandler* ppowhand, sfg::SFGUI* _gui);
	~MainMenu();
};

