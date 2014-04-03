#pragma once



class Ball : public CollidableCircle
{
private:
	LastFrameCollisions ballCol;
public:

	bool bothit{ false }, tophit{ false }, lefthit{ false }, righthit{ false };

	//Create a constant float value for the ball size.
	float ballRadius{ 10.f }, ballVelocity{ 20.f };
	
	//create a timer to use with ball movement
	Timer bTimer;

	//FileIO& operator=(const FileIO&) = delete;

	bool firstUpdate = true;

	bool lastFrameRightCol, lastFrameLeftCol, lastFrameTopCol;

	float* ballRotationSpeed;

	//window size properties
	int currentWindowHeight;
	int currentWindowWidth;

	//Create a 2 dimensional physics vector storing 2 floating point values representing the velocity.
	sf::Vector2f velocity{-ballVelocity, -ballVelocity};

	int activeSlows = 0;

	float* directionalVector;

	void changeDirection(float addition)
	{
		//calculate from cartasian vectors to radians
		*directionalVector = atan2(velocity.x, velocity.y);
		if (*directionalVector + addition >= 6.28318f) *directionalVector += addition - 6.28318f;
		else if (*directionalVector + addition < 0) *directionalVector += addition + 6.28318f;
		else *directionalVector += addition;
		//calculate back for collision detection use
		velocity.x = sin(*directionalVector) * ballVelocity;
		velocity.y = cos(*directionalVector) * ballVelocity;
	}

	//Ball constructor
	//mX > starting x coordinate
	//mY > starting y coordinate
	Ball::Ball(float mX, float mY, int wH, int wW, sf::Texture* pText)
	{
		ballRotationSpeed = new float(0.075);
		directionalVector = new float(atan2(-ballVelocity, -ballVelocity));
		bTimer.setReturnVal(false);
		//Apply the ball's position, radius, color, and origin to the circleShape
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		//shape.setFillColor(sf::Color::Green);
		shape.setOrigin(ballRadius, ballRadius);
		//Then apply the global window properties to this object
		currentWindowHeight = wH;
		currentWindowWidth = wW;
		shape.setTexture(pText);
		velocity.y = -ballVelocity;
		velocity.x = -ballVelocity;
	}

	void activateSlow()
	{
		ballVelocity = ballVelocity / 2;
		velocity.x = velocity.x / 2;
		velocity.y = velocity.y / 2;
		activeSlows++;
	}

	void activateBigBall()
	{
		shape.setRadius(shape.getRadius() * 3);
	}

	void deactivateBigBall()
	{
		shape.setRadius(shape.getRadius() / 3);
	}

	void deactivateSlow()
	{
		ballVelocity = ballVelocity * 2;
		velocity.x = velocity.x * 2;
		velocity.y = velocity.y * 2;
		activeSlows--;
	}

	void setVelocity(float v)
	{
		ballVelocity = v;
	}

	void setVel2f(sf::Vector2f vel2f)
	{
		velocity = vel2f;
	}
	
	sf::Vector2f getVel2f()
	{
		return velocity;
	}

	float getVelocity()
	{
		return ballVelocity;
	}

	//Function to update shape movement
	void update(float elapsedTime)
	{
		//Move the shape first
		if (firstUpdate)
		{
			
			shape.move(sf::Vector2f(((velocity.x * ballVelocity) / 60.f), ((velocity.y * ballVelocity) / 60.f)));
			firstUpdate = false;
		}
		else
			shape.move(sf::Vector2f(((velocity.x * ballVelocity) * elapsedTime), ((velocity.y * ballVelocity) * elapsedTime)));
		//std::cout << "shape moved on the x axis by " << std::to_string(((velocity.x * ballVelocity) * elapsedTime)) << std::endl;

		//Then check if the shape is still inside screen boundaries in the following block
		//Checking x boundaries first, then y boundaries
		//Check if it's out of bounds on the left side of the screen

		if (left() < 0 && !ballCol.leftBorder)
		{
			ballCol.leftBorder = true;
			velocity.x = -velocity.x;
		}
		else ballCol.leftBorder = false;
		//else check if it's out of bounds on the right side of the screen
		if (right() > currentWindowWidth && !ballCol.rightBorder)
		{
			ballCol.rightBorder = true;
			velocity.x = -velocity.x;
		}
		else ballCol.rightBorder = false;
		//Then check the y boundaries
		//Top boundary first
		if (top() < 0 && !ballCol.topBorder)
		{
			ballCol.topBorder = true;
			velocity.y = -velocity.y;
		}
		else ballCol.topBorder = false;
		//need a velocity vector(velocity exists) to modify and flip when needed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			changeDirection(*ballRotationSpeed * elapsedTime / 100);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			changeDirection(-*ballRotationSpeed * elapsedTime / 100);
		}

	}

	void pauseUpdate()
	{
		firstUpdate = true;
		bTimer.reset();
	}

	void resethits()
	{
		tophit = false;
		bothit = false;
		lefthit = false;
		righthit = false;
	}

};

