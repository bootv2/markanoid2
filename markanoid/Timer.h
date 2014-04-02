#pragma once
class Timer
{
private:
	sf::Clock clock;
	double timerTime;
	bool returnAsSecs;
public:
	Timer::Timer(bool retAsSecs)
	{
		returnAsSecs = retAsSecs;
		timerTime = 0;
	}

	Timer::Timer()
	{
		timerTime = 0;
		returnAsSecs = false;
	}

	double Timer::getElapsedTime()
	{
		if (returnAsSecs == true)
			return clock.getElapsedTime().asSeconds();
		else
			return clock.getElapsedTime().asMilliseconds();
	}

	double Timer::reset()
	{
		timerTime = 0;
		if (returnAsSecs == true)
			return clock.restart().asSeconds();
		else
			return clock.restart().asMilliseconds();
	}

	//BEWARE: Setting the timer also restarts the clock in this timer
	//Time in ms
	void Timer::setTimer(double time)
	{
		clock.restart();
		timerTime = time;
	}

	bool Timer::timeLeft()
	{
		if (clock.getElapsedTime().asMilliseconds() > timerTime) return false;
		else return true;
	}

	//param bool asSecs defines if the return values are as seconds, if false, return values return as milliseconds
	void Timer::setReturnVal(bool asSecs)
	{
		returnAsSecs = asSecs;
	}


	Timer::~Timer()
	{
	}


	bool active = true;
};

