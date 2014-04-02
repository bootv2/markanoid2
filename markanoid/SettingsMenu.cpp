#include <SFGUI\SFGUI.hpp>
#include <SFML\Graphics.hpp>

#include "SettingsMenu.h"


SettingsMenu::SettingsMenu()
{
}

//REQUIRED: bind all the game variable pointers that can be customized to the settings menu.(also causes initialisation of the settings menu)
void SettingsMenu::bindPTR(float* _paddleVel, float* _ballVel, float* _powVel, sf::RenderWindow* _pRW, sfg::SFGUI* pgui)
{
	paddleVel = _paddleVel;
	ballVel = _ballVel;
	powVel = _powVel;
	gui = pgui;
	pRWindow = _pRW;
	__paddleVel = new float(0);
	__ballVel = new float(0);
	__powVel = new float(0);
	//delete gui;
	//gui = new sfg::SFGUI();
	
	//pointers bound... continueing initialisation in the private init function;
	init();
}

void SettingsMenu::init()
{
	//boolean init
	cancelClicked = false;
	applyClicked = false;
	//button initialisation and addition to vector
	auto applybutton = sfg::Button::Create("apply");
	auto cancelbutton = sfg::Button::Create("cancel");
	auto navGeneral = sfg::Button::Create("General");
	auto navCTRLS = sfg::Button::Create("Controls");
	auto navBack = sfg::Button::Create("<--");

	buttonStorage.emplace_back(applybutton);
	buttonStorage.emplace_back(cancelbutton);
	buttonStorage.emplace_back(navBack);
	buttonStorage.emplace_back(navCTRLS);
	buttonStorage.emplace_back(navGeneral);

	//binding the buttons to functions:
	buttonStorage.at(0)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&SettingsMenu::applyButtonClicked, this));
	buttonStorage.at(1)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&SettingsMenu::cancelButtonClicked, this));
	buttonStorage.at(2)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&SettingsMenu::navigateBack, this));
	//buttonStorage.at(3)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&SettingsMenu::navigateToCTRLS, this));
	buttonStorage.at(4)->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&SettingsMenu::navigateToGeneralSettings, this));

	s_label = sfg::Label::Create("General");
	nav_label = sfg::Label::Create("Settings");

	//init the difficulty slider
	difficultySlider = sfg::Scale::Create();
	difficultySlider->SetRange(20, 100);

	//Creating and packing both menu boxes
	box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	navBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	navBox->Pack(nav_label);
	navBox->Pack(buttonStorage.at(2));
	navBox->Pack(buttonStorage.at(3));

	box->Pack(s_label);
	box->Pack(buttonStorage.at(0), false);
	box->Pack(buttonStorage.at(1), false);
	box->Pack(difficultySlider);

	//Window creation for box packing
	navWindow = sfg::Window::Create();
	varWindow = sfg::Window::Create();
	varWindow->SetTitle("General Settings");
	navWindow->SetTitle("Navigate");

	navWindow->Add(navBox);
	varWindow->Add(box);

	navWindow->SetAllocation(sf::FloatRect(0, 0, 300, 1000));
	varWindow->SetAllocation(sf::FloatRect(301, 0, 1600, 1000));

	//add both windows to desktop
	desktop.Add(navWindow);
	desktop.Add(varWindow);
}

//void SettingsMenu::

int SettingsMenu::run()
{
	inSetMenu = true;
	cancelClicked = false;
	navWindow->Show(true);
	varWindow->Show(true);
	int ret;
	//Reset ogl states to enable gui rendering...
		pRWindow->resetGLStates();
		pRWindow->clear(sf::Color::Black);

	//Need event and clock variables to track events and frametime.
	sf::Event ev1;
	sf::Clock guiclock;

	while (inSetMenu)
	{
		//handle events
		while (pRWindow->pollEvent(ev1))
		{
			desktop.HandleEvent(ev1);
			if (ev1.type == sf::Event::Closed)
				pRWindow->close();
		}
		//update sfgui
		desktop.Update(guiclock.restart().asSeconds());
		pRWindow->clear();
		gui->Display(*pRWindow);
		pRWindow->display();
		if (cancelClicked) inSetMenu = false;
	}
	navWindow->Show(false);
	varWindow->Show(false);
	return -1;
}


SettingsMenu::~SettingsMenu()
{
}

void SettingsMenu::applyButtonClicked()
{
	sliderPos = difficultySlider->GetValue();
	//*paddleVel = pow(sliderPos/100, 2) * (500 * paddleRatio);//Paddle velocity
	//std::cout << "paddleVel: " << pow(sliderPos / 100, 2) * (500 * paddleRatio) << std::endl;
	//std::cout << "ballVel: " << pow(sliderPos / 100, 2) * (500 * ballRatio) << std::endl;
	//std::cout << "powVel: " << pow(sliderPos / 100, 2) * (500 * powRatio) << std::endl;
	*ballVel = pow(sliderPos / 100, 2) * (500 * ballRatio);
	*paddleVel = pow(sliderPos / 100, 2) * (500 * paddleRatio);
	*powVel = pow(sliderPos / 100, 2) * (500 * powRatio);
	applyClicked = true;
}

//if the cancel button is clicked do not chance variable values, and return to the main menu.
void SettingsMenu::cancelButtonClicked()
{
	cancelClicked = true;
}

void SettingsMenu::navigateToGeneralSettings()
{

}

void SettingsMenu::navigateBack()
{
	inSetMenu = false;
}