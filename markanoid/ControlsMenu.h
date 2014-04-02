#pragma once
class ControlsMenu
{
private:
	sfg::Box::Ptr ctrlBox;
	std::vector<sfg::Widget::Ptr> buttonStorage;
	sfg::Label::Ptr title;
	sf::RenderWindow* pRWindow;
	bool buttonClicked = false;
	bool keyPressed = false;
	int buttonClickedID = -1;

	char castCharfromSFKeyPress();
	char castMappedChar();
public:
	ControlsMenu();
	void init(sf::RenderWindow* _pRWindow);
	
	~ControlsMenu();
};

