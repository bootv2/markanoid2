#pragma once
class Block
{
public:
	//-Object properties block(function())
	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float left()	{ return x(); }
	float right()	{ return x() + blockWidth; }
	float top()		{ return y(); }
	float bottom()	{ return y() + blockHeight; }
	//-End object properties block

	sf::RectangleShape shape;

	int hp = 0;

	SoundMan* pSndMan;

	bool hit = false;

	const float blockWidth{ 60.f }, blockHeight{ 20.f };
	bool destroyed;

	Block::Block(sf::Vector2f position, int _hp, SoundMan* _pSndMan)
	{
		pSndMan = _pSndMan;
		hp = _hp;
		destroyed = false;
		//--Constructor block
		//-Shape definition
		//Set shape size to the predefined size
		shape.setSize({ blockWidth, blockHeight });
		//Set the shape color to yellow
		switch (hp)
		{
		case 0:
			destroyed = true;
		case 1:
			shape.setFillColor(sf::Color::Yellow);
			break;

		case 2:
			shape.setFillColor(sf::Color::Red);
			break;

		case 3:
			shape.setFillColor(sf::Color::Magenta);
			break;

		case 4:
			shape.setFillColor(sf::Color::Green);
			break;
		}
		//Set the shape origin to it's centre instead of it's left top corner
		//shape.setOrigin(position.x + (blockWidth / 2), position.y + (blockHeight / 2));
		//And lastly, set the shape position
		shape.setPosition(position);
		//-End shape definition
		//--End constructor block
	};

	void draw(sf::RenderWindow* pRW)
	{
		if (!destroyed)
			pRW->draw(shape);
	}

	void damage(int dmg)
	{
		hp -= dmg;
		switch (hp)
		{
		case 0:
			destroyed = true;
		case 1:
			shape.setFillColor(sf::Color::Yellow);
			break;

		case 2:
			shape.setFillColor(sf::Color::Red);
			break;

		case 3:
			shape.setFillColor(sf::Color::Magenta);
			break;
		}
	}

	void testCollision(Ball* pBall)
	{
		if (destroyed) return;
		if (pBall->right() >= left() && pBall->left() <= right() && pBall->bottom() >= top() && pBall->top() <= bottom())
		{
			std::cout << "ball/block intersection found\n";
			pSndMan->playBlockBreakSound();
			damage(1);

			hit = true;//need to see if its hit to see if a powerup might be spawned

			//Directional intersection calculation block
			float leftOverlap{ pBall->right() - left() };
			float rightOverlap{ right() - pBall->left() };
			float topOverlap{ pBall->bottom() - top() };
			float bottomOverlap{ bottom() - pBall->top() };

			//If the overlap from the left is greater than from the right, its safe to assume the ball hit the block from the left 
			bool ballFromLeft(abs(leftOverlap) < abs(rightOverlap));
			// apply the same principle for top/bot collisions
			bool ballFromTop(abs(topOverlap) < abs(bottomOverlap));

			//Store the min overlaps for the x and y axises
			float minOverlapX{ ballFromLeft ? leftOverlap : rightOverlap };
			float minOverlapY{ ballFromTop ? topOverlap : bottomOverlap };

			//if the magnitude of the x overlap is less than the magnitude of the y overlap we can safely assume that the ball hit the brick vertically;
			//then, upon our assumptions, we change either the x or y veolocity of the ball, creatig a realistic response for the collision
			if (abs(minOverlapX) < abs(minOverlapY)) pBall->velocity.x = ballFromLeft ? 0 - pBall->velocity.x : pBall->velocity.x;

			else pBall->velocity.y = ballFromTop ? 0 - pBall->velocity.y : pBall->velocity.y;

		}
	}
};

