#pragma once
class PowerupContainer
{
public:
	sf::CircleShape* shape;

	sf::Vector2f containerFallingSpeed{ 0.f, 260.f };

	bool* isExisting;

	int* powID;

	Timer* pcTimer;

	bool* firstUpdate;

	ResMan* globResMan;

	//Powerup container properties Block
	float x()		{ return shape->getPosition().x; }
	float y()		{ return shape->getPosition().y; }
	float left()	{ return x() - 10.f; }
	float right()	{ return x() + 10.f; }
	float top()		{ return y() - 10.f; }
	float bottom()	{ return y() + 10.f; }


	PowerupContainer()
	{
		
		
	}

	PowerupContainer(Block& mBlock, float fallSpeed, int maxPowID, ResMan* _res, std::vector<std::string> powPaths)
	{
		pcTimer = new Timer();
		pcTimer->setReturnVal(true);
		shape = new sf::CircleShape();
		isExisting = new bool(true);
		firstUpdate = new bool(true);
		globResMan = _res;
		containerFallingSpeed.y = fallSpeed;
		shape->setPosition(mBlock.x(), mBlock.y());
		powID = new int(rand() % maxPowID);
		shape->setRadius(10.f);
		shape->setTexture(globResMan->getTexture(powPaths.at(*powID)));
		shape->setOrigin(10.f, 10.f);
	}

	//The powerup container reConstructor function, it takes a Block as an argument because
	//the powerup container ball is created at the coordinates the destroyed block used to reside
	void createContainer(Block& mBlock, float fallSpeed, int maxPowID, ResMan* _res, std::vector<std::string> powPaths)
	{
		pcTimer = new Timer();
		pcTimer->setReturnVal(true);
		shape = new sf::CircleShape();
		isExisting = new bool(true);
		firstUpdate = new bool(true);
		globResMan = _res;
		containerFallingSpeed.y = fallSpeed;
		shape->setPosition(mBlock.x(), mBlock.y());
		powID = new int(rand() % maxPowID);
		shape->setRadius(10.f);
		shape->setTexture(globResMan->getTexture(powPaths.at(*powID)));
		shape->setOrigin(10.f, 10.f);
	}

	int getPowID()
	{
		return *powID;
	}

	bool existing()
	{
		return *isExisting;
	}

	void setExisting(bool exist)
	{
		*isExisting = exist;
	}

	void setFallingSpeed(float vel)
	{
		containerFallingSpeed.y = vel;
	}

	sf::CircleShape* getShapeAddress()
	{
		return shape;
	}

	void update()
	{
		float elapsedTime = pcTimer->reset();
		if (firstUpdate)
		{
			shape->move(containerFallingSpeed.x, containerFallingSpeed.y / 60);
			firstUpdate = false;
		}
		else
		{
			shape->move(sf::Vector2f(containerFallingSpeed.x * elapsedTime, containerFallingSpeed.y * elapsedTime));
		}
	}

	void pausedUpdate()
	{
		*firstUpdate = true;
		pcTimer->reset();
	}

	void setTexture(sf::Texture* _pText)
	{
		shape->setTexture(_pText);
	}

};

