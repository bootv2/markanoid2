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

	ResMan* prMan;

	bool hit = false;

	bool tophit, bothit, lefthit, righthit;

	const float blockWidth{ 60.f }, blockHeight{ 20.f };
	bool destroyed;

	Block::Block(sf::Vector2f position, int _hp, SoundMan* _pSndMan, ResMan* _prMan)
	{
		prMan = _prMan;
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
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/1hp.png"));
			break;

		case 2:
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/2hp.png"));
			break;

		case 3:
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/3hp.png"));
			break;

		case 4:
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/4hp.png"));
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
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/1hp.png"));
			break;

		case 2:
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/2hp.png"));
			break;

		case 3:
			shape.setTexture(prMan->getTexture("res/txt/kenney.nl/blocks/3hp.png"));
			break;
		}
	}

	void testCollision(Ball* pBall)
	{
		if (destroyed) return;
		if (pBall->right() >= left() && pBall->left() <= right() && pBall->bottom() >= top() && pBall->top() <= bottom())
		{

			pSndMan->playBlockBreakSound();
			damage(1);

			hit = true;//need to see if its hit to see if a powerup might be spawned

			//Directional intersection calculation block
			float leftOverlap{ pBall->right() - left() };
			float rightOverlap{ right() - pBall->left() };
			float topOverlap{ pBall->bottom() - top() };
			float bottomOverlap{ bottom() - pBall->top() };

			//If the overlap from the left is greater than from the right, its safe to assume the ball hit the block from the left 
			bool ballFromLeft(abs(leftOverlap) <= abs(rightOverlap));
			// apply the same principle for top/bot collisions
			bool ballFromTop(abs(topOverlap) <= abs(bottomOverlap));

			//Store the min overlaps for the x and y axises
			float minOverlapX{ ballFromLeft ? leftOverlap : rightOverlap };
			float minOverlapY{ ballFromTop ? topOverlap : bottomOverlap };

			//if the magnitude of the x overlap is less than the magnitude of the y overlap we can safely assume that the ball hit the brick vertically;
			//then, upon our assumptions, we change either the x or y veolocity of the ball, creatig a realistic response for the collision
			if (abs(minOverlapX) <= abs(minOverlapY))
			{
				if (ballFromLeft)
				{
					if (!pBall->lefthit)
					{
						pBall->velocity.x = 0 - pBall->velocity.x;
						pBall->lefthit = true;
					}
				}
				else if (!pBall->righthit)
				{
					pBall->velocity.x = pBall->velocity.x * -1;
					pBall->righthit = true;
				}
			}

			else  if (ballFromTop)
			{
				if (!pBall->tophit)
				{
					pBall->velocity.y = 0 - pBall->velocity.y;
					pBall->tophit = true;
				}

			}
				
			else
			{
				if (!pBall->bothit)
				{
					pBall->velocity.y = pBall->velocity.y * -1;
					pBall->bothit = true;
				}
			}
		}
	}
};

