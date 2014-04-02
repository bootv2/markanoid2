#pragma once
class SettingsMenu
{
private:
	float *paddleVel, *ballVel, *powVel;//real value storage, only to be altered when apply is pressed.
	float *__paddleVel, *__ballVel, *__powVel;//temporary value storage that gets used after pressing apply
	float sliderPos = 25;
	float paddleRatio = 1.8f;
	float ballRatio = 0.075f;
	float powRatio = 1.35f;

	//gui and gui drawing variables
	sfg::SFGUI* gui;
	std::vector<sfg::Widget::Ptr> buttonStorage;
	sf::RenderWindow* pRWindow; 
	sfg::Label::Ptr s_label;
	sfg::Label::Ptr nav_label;
	sfg::Desktop desktop;
	sfg::Window::Ptr varWindow;
	sfg::Window::Ptr navWindow;                                    
	sfg::Box::Ptr box;
	sfg::Box::Ptr navBox;
	sfg::Scale::Ptr difficultySlider;

	//still in settings menu boolean
	bool inSetMenu = true;
	bool inCTRLSMenu = false;

	//buttonsclicked
	bool cancelClicked, applyClicked;

	//settings menu visible menu index
	int setIndex;

	void applyButtonClicked();
	void cancelButtonClicked();
	void navigateToGeneralSettings();
	void navigateBack();
	//void navigateToCTRLS();

	void init();

public:
	SettingsMenu();
	int run();
	void bindPTR(float* _paddleVel, float* _ballVel, float* _powVel, sf::RenderWindow* _pRW, sfg::SFGUI* pgui);
	~SettingsMenu();
};

