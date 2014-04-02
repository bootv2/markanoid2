#pragma once



class Paddle
{
public:
	//-Object properties block(function())
	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float left()	{ return x() - shape.getSize().x / 2; }
	float right()	{ return x() + shape.getSize().x / 2; }
	float top()		{ return y() - paddleHeight / 2; }
	float bottom()	{ return y() + paddleHeight / 2; }
	//-End object properties block

	float paddleWidth{ 100.f }, paddleHeight{ 20.f }, paddleVelocity{ 450.f };

	bool firstUpdate = true;

	Timer* pTimer;

	sf::RectangleShape shape;
	sf::Vector2f velocity;
	int windowWidth, windowHeight;
	//Player Paddle constructor
	Paddle(int wW, int wH)
	{
		pTimer = new Timer(true);
		//--Constructor block
		//-Shape definition
		//Set shape size to the predefined size
		shape.setSize({ paddleWidth, paddleHeight });
		//Set the shape color to green
		shape.setFillColor(sf::Color::Blue);
		//Set the shape origin to it's centre instead of it's left top corner
		shape.setOrigin(x() + (paddleWidth / 2), y() + (paddleHeight / 2));
		//And lastly, set the shape position
		shape.setPosition((float )wW / 2, wH - 50);
		//-End shape definition
		
		//Define the local window size variables from arguments
		windowWidth = wW; windowHeight = wH;

		//Construct the velocity Vector2f
		velocity = sf::Vector2f(0.f, 0.f);
		//--End constructor block
	}

	void setPaddleVelocity(float v)
	{
		paddleVelocity = v;
	}

	float getPaddleVelocity()
	{
		return paddleVelocity;
	}

	void update()
	{
		//In this block the program checks for keypresses
		//Check if right is pressed, if so, adjust velocity for the object to move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowWidth) velocity = sf::Vector2f(paddleVelocity, 0.f);
		//Else check if left is pressed, if so, adjust velocity for the object to move left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0) velocity = sf::Vector2f(-paddleVelocity, 0.f);
		//Else, no velocity, because there is no user input registered
		else velocity = sf::Vector2f(0.f, 0.f);

		//move the shape according to the current velocity vector
		//Move the shape first
		if (firstUpdate)
		{
			shape.move(sf::Vector2f(velocity.x / 60.f, velocity.y));
			firstUpdate = false;
		}
		else
			shape.move(sf::Vector2f(velocity.x * pTimer->reset(), velocity.y));
		pTimer->reset();
	}

	void powerup()
	{
		shape.setOrigin(sf::Vector2f(shape.getSize().x, paddleHeight / 2));
		shape.setSize(sf::Vector2f(shape.getSize().x * 2, paddleHeight));
	}

	void powReset()
	{
		shape.setOrigin(sf::Vector2f(shape.getSize().x / 4, paddleHeight / 2));
		shape.setSize(sf::Vector2f(shape.getSize().x / 2, paddleHeight));
	}

	void pauseUpdate()
	{
		firstUpdate = true;
		pTimer->reset();
	}

};

